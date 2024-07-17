cmake_minimum_required(VERSION 3.16.0)

include(cmake/ConfigureNRF.cmake)

#We can use the CMake script to download the SDK
#set(NRF_SDK_ROOT_DIR C:/Users/zadock-maloba/Documents/nRF5_SDK_17.1.0_ddde560)
set(DOWNLOAD_NRF_SDK ON)

set (NRF_PROJ_SRCS src/main.c src/config.c)
set (NRF_PROJ_INCL include/config.h)

project(Segger-Config)

configure_nrf_project(ArduCAM_SPI_INACTIVE TEST)