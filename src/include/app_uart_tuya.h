#ifndef SRC_INCLUDE_APP_UART_TUYA_H_
#define SRC_INCLUDE_APP_UART_TUYA_H_

#define FLAG_START1         0x55
#define FLAG_START2         0xAA
#define SP_VERSION          0x02
#define DATA_MAX_LEN        64          /* do not change!   */
#define HYSTERESIS_MIN      1
#define HYSTERESIS_MAX      5
#define SET_POINT_MIN_MIN   5
#define SET_POINT_MIN_MAX   15
#define SET_POINT_MAX_MIN   15
#define SET_POINT_MAX_MAX   45


typedef enum {
    COMMAND00   =   0x00,
    COMMAND01,                      /* Query product information    */
    COMMAND02,                      /* Sync module’s network status */
    COMMAND03,
    COMMAND04,
    COMMAND05,
    COMMAND06,
    COMMAND24   =   0x24,           /* Sync time                    */
} command_t;


typedef enum {
    STATUS_NET_FREE = 0,
    STATUS_NET_CONNECTED,
    STATUS_NET_ERROR,
    STATUS_NET_IN_PROGRESS,
    STATUS_NET_UNKNOWN
} status_net_t;

typedef enum {
    SENSOR_IN   = 0x00,
    SENSOR_AL   = 0x01,
    SENSOR_OU   = 0x02
} sensor_type_t;

typedef struct __attribute__((packed)) {
    uint8_t  f_start1;
    uint8_t  f_start2;
    uint8_t  pkt_vesion;
    uint16_t seq_num;
    uint8_t  command;
    uint16_t len;
    uint8_t  data[DATA_MAX_LEN];
    uint16_t pkt_len;
} pkt_tuya_t;

typedef struct __attribute__((packed)) {
    uint8_t  dp_id;
    uint8_t  dp_type;
    uint16_t dp_len;
    uint8_t  data[DATA_MAX_LEN-8];
    uint16_t len;
} data_point_t;


typedef struct {
    uint8_t    confirm_need;
    uint8_t    confirm_rec;
    pkt_tuya_t pkt;
} cmd_queue_cell_t;

typedef struct {
    uint8_t cmd_num;
    cmd_queue_cell_t cmd_queue[5];
} cmd_queue_t;

uint8_t checksum(uint8_t *data, uint16_t length);
void uart_cmd_handler();
void set_status_net(status_net_t new_status);
uint16_t get_seq_num();
void set_seq_num(uint16_t f_seq_num);
void set_header_pkt(uint8_t *f_pkt_buff, uint8_t len, uint16_t f_seq_num, uint8_t command);
//uint8_t get_queue_cnt();
void add_cmd_queue(pkt_tuya_t *pkt, uint8_t confirm_need);


#endif /* SRC_INCLUDE_APP_UART_TUYA_H_ */
