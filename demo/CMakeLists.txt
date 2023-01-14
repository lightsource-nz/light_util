add_executable(light_util_demo)

target_sources(light_util_demo PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/main.c)

target_link_libraries(
        light_util_demo PUBLIC
        light_util
)
if(NOT PICO_NO_HARDWARE)
        pico_enable_stdio_semihosting(light_util_demo 1)
        target_link_libraries(light_util_demo PUBLIC pico_stdlib)
endif()
pico_add_extra_outputs(light_util_demo)
