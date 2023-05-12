cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

project(light_util C CXX ASM)

pico_sdk_init()

add_subdirectory(demo)

add_library(light_util INTERFACE)

target_include_directories(
    light_util
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources(
    light_util
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/light_util.c
    ${CMAKE_CURRENT_LIST_DIR}/src/list.c
)

# mode defaults to production
if(NOT DEFINED LIGHT_RUN_MODE)
    message("LIGHT_RUN_MODE not set, defaulting to PRODUCTION")
    set(LIGHT_RUN_MODE PRODUCTION)
else()
    message("LIGHT_RUN_MODE is set to ${LIGHT_RUN_MODE}")
endif()

target_compile_definitions(
    light_util INTERFACE
    RUN_MODE=${LIGHT_RUN_MODE}
)
if(DEFINED COMPILE_LOG_LEVEL)
    message("COMPILE_LOG_LEVEL is set to ${COMPILE_LOG_LEVEL}")
    target_compile_definitions(
        light_util
        INTERFACE
        FILTER_LOG_LEVEL=${COMPILE_LOG_LEVEL}
    )
endif()

if(DEFINED LIGHT_API_TRACE)
    target_compile_definitions(
        light_util
        INTERFACE
        LIGHT_API_TRACE
    )
endif()

# pico_platform must be linked to correctly define PICO_RP2040 in on-device builds
target_link_libraries(
    light_util
    INTERFACE
    pico_platform
)
