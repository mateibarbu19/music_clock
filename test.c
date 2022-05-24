#include <stdio.h>
#include "pico/stdlib.h"

/* SDCard Dependencies */
#include "f_util.h"
#include "ff.h"
#include "rtc.h"
#include "hw_config.h"

int main() {
    stdio_init_all();                                                                                         
    time_init();

    puts("Init");
    sleep_ms(10000);
    puts("After init!");
    sd_card_t *pSD = sd_get_by_num(0);
    FRESULT fr = f_mount(&pSD->fatfs, pSD->pcName, 1);
    if (FR_OK != fr) panic("f_mount error: %s (%d)\n", FRESULT_str(fr), fr);
    FIL fil;

    puts("Hello, world!");
    const char* const filename = "filename.txt";
    fr = f_open(&fil, filename, FA_CREATE_ALWAYS | FA_WRITE);
    if (FR_OK != fr && FR_EXIST != fr)
        panic("f_open(%s) error: %s (%d)\n", filename, FRESULT_str(fr), fr);
    if (f_printf(&fil, "Hello, world!\n") < 0) {
        printf("f_printf failed\n");
    }
    fr = f_close(&fil);
    if (FR_OK != fr) {
        printf("f_close error: %s (%d)\n", FRESULT_str(fr), fr);
    }

    puts("Goodbye, world!");
    f_unmount(pSD->pcName);
}
