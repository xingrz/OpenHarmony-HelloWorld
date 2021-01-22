#include <stdio.h>
#include <unistd.h>
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

    int offset = SCREEN_WIDTH;
    while (1)
    {
        int sx = offset > 0 ? 0 : -offset;
        int dx = offset > 0 ? offset : 0;

        gui_fill(0x0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        gui_draw((uint8_t *)text, SW, SH, sx, 0, dx, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        ssd1322_draw(gui_render());

        usleep(500);

        offset -= 2;
        if (offset <= -SW)
            offset = SCREEN_WIDTH;
    }
}

SYS_RUN(HelloWorld);
