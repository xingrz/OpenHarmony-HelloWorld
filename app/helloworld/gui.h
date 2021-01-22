#ifndef _RETRPL_GUI_
#define _RETRPL_GUI_

#include <stdint.h>

void *gui_render(void);

void gui_fill(uint8_t color, int dx, int dy, int dw, int dh);
void gui_draw(uint8_t *p, int sw, int sh, int sx, int sy, int dx, int dy, int dw, int dh);

#endif // _RETRPL_GUI_
