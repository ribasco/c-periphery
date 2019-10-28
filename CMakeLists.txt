cmake_minimum_required(VERSION 3.15)
project(c_periphery C)

set(CMAKE_C_STANDARD 11)

include_directories(src)
include_directories(tests)

add_library(cperiphery STATIC
        src/gpio.c
        src/gpio.h
        src/i2c.c
        src/i2c.h
        src/mmio.c
        src/mmio.h
        src/serial.c
        src/serial.h
        src/spi.c
        src/spi.h
        src/version.c
        src/version.h
        tests/test.h
        tests/test_gpio.c
        tests/test_gpio_sysfs.c
        tests/test_i2c.c
        tests/test_mmio.c
        tests/test_serial.c
        tests/test_spi.c)
