#include <stdio.h>
#include <unistd.h>

#include "ssd1322.h"
#include "pinout.h"

#define COUNT(x) (sizeof(x) / sizeof(x[0]))

#define TAG "ssd1322"

static struct
{
	uint8_t cmd;
	uint8_t len;
	uint8_t data[2];
} ssd1322_reg_conf[] = {
	{0xFD, 1, {0x12}},		 // Command Lock
	{0xAE, 0, {}},			 // Sleep In
	{0xB3, 1, {0x91}},		 // Set Display Clock Divide Ratio/Oscillator Frequency
	{0xCA, 1, {0x3f}},		 // Set Multiplex Ratio
	{0xA2, 1, {0x00}},		 // Set Display Offset
	{0xA1, 1, {0x00}},		 // Set Display Start Line
	{0xA0, 1, {0x06}},		 // Set Re-Map $ Dual COM Line Mode
	{0xB5, 1, {0x00}},		 // Set GPIO
	{0xAB, 1, {0x01}},		 // Function Selection
	{0xB4, 2, {0xA0, 0xFD}}, // Enable External VSL
	{0xC1, 1, {0xFF}},		 // Set Contrast Current
	{0xC7, 1, {0x0F}},		 // Master Contrast Current Control
	{0xB9, 0, {}},			 // Select Default Linear Gray Scale Table
	{0xB1, 1, {0xE2}},		 // Set Phase Length
	{0xD1, 2, {0x82, 0x20}}, // Enhance Driving Scheme Capability
	{0xBB, 1, {0x1F}},		 // Set Pre-Charge Voltage
	{0xB6, 1, {0x08}},		 // Set Second Pre-Charge Period
	{0xBE, 1, {0x07}},		 // Set VCOMH Deselect Level
	{0xA6, 0, {}},			 // Set Display Mode
	{0xAF, 0, {}},			 // Sleep Out
};

static void
write_reg(uint8_t val)
{
	GpioSetOutputVal(PIN_OLED_DC, 0);
	hspi_write(&val, sizeof(uint8_t));
}

static void
write_data(void *buf, uint32_t len)
{
	GpioSetOutputVal(PIN_OLED_DC, 1);
	hspi_write(buf, len);
}

static void
write_data8(uint8_t val)
{
	GpioSetOutputVal(PIN_OLED_DC, 1);
	hspi_write(&val, sizeof(uint8_t));
}

void ssd1322_init(void)
{
	IoSetFunc(WIFI_IOT_IO_NAME_GPIO_11, WIFI_IOT_IO_FUNC_GPIO_11_GPIO);
	IoSetFunc(WIFI_IOT_IO_NAME_GPIO_12, WIFI_IOT_IO_FUNC_GPIO_12_GPIO);

	GpioInit();
	GpioSetDir(PIN_OLED_DC, WIFI_IOT_GPIO_DIR_OUT);
	GpioSetDir(PIN_OLED_RST, WIFI_IOT_GPIO_DIR_OUT);

	printf("[I][%s]Reset panel...\n", TAG);
	GpioSetOutputVal(PIN_OLED_RST, 0);
	usleep(200 * 1000);
	GpioSetOutputVal(PIN_OLED_RST, 1);

	printf("[I][%s]Init SSD1322...\n", TAG);

	for (unsigned int i = 0; i < COUNT(ssd1322_reg_conf); i++)
	{
		write_reg(ssd1322_reg_conf[i].cmd);
		if (ssd1322_reg_conf[i].len > 0)
		{
			write_data(ssd1322_reg_conf[i].data, ssd1322_reg_conf[i].len);
		}
	}
}

static void
ssd1322_prepare(void)
{
	// Set Column Address
	write_reg(0x15);
	write_data8(0x1C + 0);
	write_data8(0x1C + SCREEN_WIDTH / 4 - 1);

	// Set Row Address
	write_reg(0x75);
	write_data8(0);
	write_data8(SCREEN_HEIGHT - 1);

	// Write RAM
	write_reg(0x5C);
}

void ssd1322_fill(uint8_t color)
{
	uint8_t pt[SCREEN_PIXELS / 2];
	for (unsigned int i = 0; i < sizeof(pt); i++)
	{
		pt[i] = (color & 0xF) | ((color & 0xF) << 4);
	}

	ssd1322_prepare();
	write_data(pt, sizeof(pt));
}

void ssd1322_draw(uint8_t *pixels)
{
	ssd1322_prepare();
	write_data(pixels, SCREEN_PIXELS / 2);
}
