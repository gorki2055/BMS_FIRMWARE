# ==============================================================================
# Makefile for 21S 70Ah NCM BMS Firmware (N32G452 Cortex-M4F)
# ==============================================================================

TARGET = bms_firmware
BUILD_DIR = build

# Toolchain definitions
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

# Architecture & Hardware Floating Point Flags
CPU     = -mcpu=cortex-m4
FPU     = -mfpu=fpv4-sp-d16
FLOAT   = -mfloat-abi=hard
MCU     = $(CPU) -mthumb $(FPU) $(FLOAT)

# C Includes
C_INCLUDES = \
	-Iinclude \
	-Icmsis

# Compiler Flags
CFLAGS = $(MCU) $(C_INCLUDES) -O2 -Wall -fdata-sections -ffunction-sections -std=c99

# Linker Script & Flags
LDSCRIPT = n32g45x_flash.ld
LDFLAGS  = $(MCU) -T$(LDSCRIPT) -Wl,--gc-sections -specs=nano.specs -specs=nosys.specs -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref

# C Sources
C_SOURCES = \
	src/main.c \
	src/bms_core.c \
	src/bms_can.c \
	src/bms_parallel.c \
	src/dvc1124_afe.c \
	src/bms_ocv.c \
	src/bms_hal.c \
	cmsis/startup_n32g45x.c

# Object files
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-gnms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SIZE) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf
	$(OBJCOPY) -O ihex $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(OBJCOPY) -O binary -S $< $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
