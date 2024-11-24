#include "tl_common.h"

#include "app_main.h"

uart_data_t rec_buff = {0,  {0, } };
uint8_t  ring_buff[RING_BUFF_SIZE];
uint16_t ring_head, ring_tail;
uint8_t uart_msg_err;

void print_pkt(uint8_t *data, uint32_t len, uint8_t dir) {

#if UART_PRINTF_MODE && DEBUG_PKT

    uint8_t ch;

    printf("%spkt %s 0x", dir?"out_":"inp_", dir?"<==":"==>");

     for (int i = 0; i < len; i++) {
         ch = data[i];
         if (ch < 0x10) {
             printf("0%x", ch);
         } else {
             printf("%x", ch);
         }
     }
     printf("\r\n");
#endif
}


uint8_t available_ring_buff() {
    if (ring_head != ring_tail) {
        return true;
    }
    return false;
}

size_t get_queue_len_ring_buff() {
   return (ring_head - ring_tail) & (RING_BUFF_MASK);
}

static size_t get_freespace_ring_buff() {
    return (sizeof(ring_buff)/sizeof(ring_buff[0]) - get_queue_len_ring_buff());
}

void flush_ring_buff() {
    ring_head = ring_tail = 0;
    memset(ring_buff, 0, RING_BUFF_SIZE);
}

uint8_t read_byte_from_ring_buff() {
    uint8_t ch = ring_buff[ring_tail++];
    ring_tail &= RING_BUFF_MASK;
    return ch;

}

size_t read_bytes_from_buff(uint8_t *str, size_t len) {
    size_t i;

    for (i = 0; i < len; i++) {
        str[i] = read_byte_from_ring_buff();
    }



    return i;
}

static size_t write_bytes_to_ring_buff(uint8_t *data, size_t len) {

    size_t free_space = get_freespace_ring_buff();
    size_t put_len;

    if (free_space >= len) put_len = len;
    else put_len = free_space;

    for (int i = 0; i < put_len; i++) {
        ring_buff[ring_head++] = data[i];
        ring_head &= RING_BUFF_MASK;
    }

    return put_len;
}


static void app_uartRecvCb() {

    uint8_t st = SUCCESS;

#if PM_ENABLE
    not_sleep = true;
#endif

    if(rec_buff.dma_len == 0) {
        st = UART_MSG_STATUS_UART_EXCEPT;
    }

    if(rec_buff.dma_len > UART_DATA_LEN) {
        st = UART_MSG_STATUS_MSG_OVERFLOW;
    }

    if (st == SUCCESS) {

        print_pkt(rec_buff.data, rec_buff.dma_len, 0);

        write_bytes_to_ring_buff(rec_buff.data, rec_buff.dma_len);
    }

//    printf("st: 0x%x, rec_buff.dma_len: %d\r\n", st, rec_buff.dma_len);

    rec_buff.dma_len = 0;

    uart_msg_err = st;
}

uartTx_err app_uart_txMsg(uint8_t *data, uint8_t len) {


    print_pkt(data, len, 1);

    if (drv_uart_tx_start(data, len)) return UART_TX_SUCCESS;

    return UART_TX_FAILED;
}

void app_uart_init(uint32_t baudrate) {

    flush_ring_buff();
    drv_uart_pin_set(GPIO_UART_TX, GPIO_UART_RX);

    drv_uart_init(BAUDRATE_UART, (uint8_t*)&rec_buff, sizeof(uart_data_t), app_uartRecvCb);
}
