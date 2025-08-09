#include <cmath>
#include <cstdio>
#include "pico/stdlib.h"
#include "pico/bootrom.h"

int main() {
    stdio_init_all();
    printf("starting Lokey test\n");
    reset_usb_boot(0, 0);
}
