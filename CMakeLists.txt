cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(test_project C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# add the SD Card library
add_subdirectory(
    lib/no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI
    build
)

# Add executable. Default name is the project name
add_executable(${PROJECT_NAME}
    test.c
    hw_config.c
)

# Add the standard library and FatFS/SPI to the build
target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    FatFs_SPI
)

target_compile_options(${PROJECT_NAME}
    PUBLIC
    -Wall
    -Wextra
    -Wno-unused-function
    -Wno-unused-parameter
)

# enable usb, disable uart
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(${PROJECT_NAME})
