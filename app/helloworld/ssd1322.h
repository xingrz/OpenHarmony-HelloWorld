#ifndef _RETRPL_SSD1322_
#define _RETRPL_SSD1322_

#include <stdint.h>
#include <stdbool.h>
#include "hspi.h"

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 64

#define SCREEN_PIXELS (SCREEN_WIDTH * SCREEN_HEIGHT)

void ssd1322_init(void);

void ssd1322_fill(uint8_t color);
void ssd1322_draw(uint8_t *pixels);

#endif // _RETRPL_SSD1322_
