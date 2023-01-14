#include<light_util.h>

#include<stdio.h>

#ifdef PICO_RP2040
#   include <pico/stdio.h>
#endif

int main(int argc, char *argv[])
{
#ifdef PICO_RP2040
    stdio_init_all();
#endif
    const uint8_t *format = "%s logging enabled";
    light_error(format, "error");
    light_warn(format, "warn");
    light_info(format, "info");
    light_debug(format, "debug");
    light_trace(format, "trace");
    printf("LIGHT_MAX_LOG_LEVEL=%d\n", LIGHT_MAX_LOG_LEVEL);
}
