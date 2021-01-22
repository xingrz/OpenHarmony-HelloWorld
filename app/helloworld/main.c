#include <stdio.h>
#include "ohos_init.h"
#include "ohos_types.h"

#include "pinout.h"
#include "hspi.h"
#include "ssd1322.h"

void HelloWorld(void)
{
    printf("=========================\n");
    printf(" 极 其 优 秀 ， 弹 性 很 足\n");
    printf("=========================\n");

    hspi_init();
    ssd1322_init();

    ssd1322_fill(0xF);
}

SYS_RUN(HelloWorld);
