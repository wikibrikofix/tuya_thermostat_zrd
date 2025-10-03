# Add inputs and outputs from these tool invocations to the build variables 

OUT_DIR += \
/$(SRC_PATH)/common \
/$(SRC_PATH)/bootLoader

OBJS += \
$(OUT_PATH)/$(SRC_PATH)/common/firmwareEncryptChk.o \
$(OUT_PATH)/$(SRC_PATH)/bootLoader/bootloader.o \
$(OUT_PATH)/$(SRC_PATH)/bootLoader/main.o 

# Each subdirectory must supply rules for building sources it contributes
$(OUT_PATH)/$(SRC_PATH)/%.o: $(SRC_PATH)/%.c 
	@echo 'Building file: $<'
	@$(CC) $(GCC_FLAGS) $(INCLUDE_PATHS) -c -o"$@" "$<"
