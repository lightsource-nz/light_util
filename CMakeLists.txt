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

target_link_libraries(
    light_util
    INTERFACE
)
