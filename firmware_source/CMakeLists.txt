cmake_minimum_required(VERSION 3.20)
project(BmsFirmware C ASM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Cortex-M4F Architecture Flags
set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MCU_FLAGS} -Wall -Wextra -O2 -ffunction-sections -fdata-sections")

# Include directories
include_directories(
    include
    cmsis
)

# Source files
set(SOURCES
    src/main.c
    src/bms_core.c
    src/bms_can.c
    src/bms_parallel.c
    src/dvc1124_afe.c
    src/bms_ocv.c
    src/bms_hal.c
    cmsis/startup_n32g45x.c
)

add_executable(${PROJECT_NAME}.elf ${SOURCES})

# Linker options
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/n32g45x_flash.ld)
target_link_options(${PROJECT_NAME}.elf PRIVATE
    -T${LINKER_SCRIPT}
    ${MCU_FLAGS}
    -Wl,--gc-sections
    -Wl,-Map=${PROJECT_NAME}.map
    --specs=nano.specs
    --specs=nosys.specs
)

# Generate HEX and BIN outputs
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.bin
    COMMENT "Building ${PROJECT_NAME}.hex and ${PROJECT_NAME}.bin"
)
