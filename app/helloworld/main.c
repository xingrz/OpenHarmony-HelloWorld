#include <stdio.h>
#include "ohos_init.h"
#include "ohos_types.h"

#include "pinout.h"
#include "hspi.h"
#include "ssd1322.h"

#include "text.h"
#include "gui.h"

#define SW 456
#define SH 64

void HelloWorld(void)
{
    printf("=========================\n");
    printf(" 极 其 优 秀 ， 弹 性 很 足\n");
    printf("=========================\n");

    hspi_init();
    ssd1322_init();

    ssd1322_fill(0x0);

    gui_draw((uint8_t *)text, SW, SH, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    ssd1322_draw(gui_render());
}

SYS_RUN(HelloWorld);
