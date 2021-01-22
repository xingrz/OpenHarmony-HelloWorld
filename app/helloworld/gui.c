#include "gui.h"
#include "ssd1322.h"

uint8_t canvas[SCREEN_PIXELS] = {0};
uint8_t buffer[SCREEN_PIXELS / 2] = {0};

void *
gui_render(void)
{
	for (int i = 0; i < SCREEN_PIXELS; i += 2)
	{
		uint8_t pl = canvas[i + 0] & 0xF;
		uint8_t pr = canvas[i + 1] & 0xF;
		buffer[(SCREEN_PIXELS - 1 - i) / 2] = (pr << 4) | pl;
	}
	return &buffer;
}

static void
gui_limit(int *dx, int *dy, int *dw, int *dh)
{
	if (*dx > SCREEN_WIDTH - 1)
		*dx = SCREEN_WIDTH - 1;
	if (*dy > SCREEN_HEIGHT - 1)
		*dy = SCREEN_HEIGHT - 1;
	if (*dx + *dw > SCREEN_WIDTH)
		*dw = SCREEN_WIDTH - *dx - 1;
	if (*dy + *dh > SCREEN_HEIGHT)
		*dh = SCREEN_HEIGHT - *dy - 1;
}

void gui_fill(uint8_t color, int dx, int dy, int dw, int dh)
{
	gui_limit(&dx, &dy, &dw, &dh);

	color &= 0xF;
	for (int y = 0; y < dh; y++)
	{
		for (int x = 0; x < dw; x++)
		{
			canvas[SCREEN_WIDTH * (dy + y) + (dx + x)] = color;
		}
	}
}

void gui_draw(uint8_t *p, int sw, int sh, int sx, int sy, int dx, int dy, int dw, int dh)
{
	gui_limit(&dx, &dy, &dw, &dh);

	if (sx > sw - 1)
		sx = sw - 1;
	if (sy > sh - 1)
		sy = sh - 1;

	if (dw > sw - sx)
		dw = sw - sx;
	if (dh > sh - sy)
		dh = sh - sy;

	uint8_t pt;
	for (int y = 0; y < dh; y++)
	{
		for (int x = 0; x < dw; x++)
		{
			pt = p[sw / 2 * (sy + y) + (sx + x) / 2];
			if ((sx + x) % 2 == 0)
			{
				pt = (pt >> 4) & 0xF;
			}
			else
			{
				pt = pt & 0xF;
			}
			canvas[SCREEN_WIDTH * (dy + y) + (dx + x)] = pt;
		}
	}
}
