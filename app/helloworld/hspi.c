#include <stdio.h>

#include "hspi.h"
#include "pinout.h"

#include "wifiiot_errno.h"

#define TAG "hspi"

void hspi_init(void)
{
	IoSetFunc(WIFI_IOT_IO_NAME_GPIO_9, WIFI_IOT_IO_FUNC_GPIO_9_SPI0_TXD);
	IoSetFunc(WIFI_IOT_IO_NAME_GPIO_10, WIFI_IOT_IO_FUNC_GPIO_10_SPI0_CK);

	WifiIotSpiCfgInitParam spi_init = {.isSlave = 0, .pad = 0};

	const WifiIotSpiCfgBasicInfo spi_cfg = {
		.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1,
		.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1,
		.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MOTOROLA,
		.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_8BIT,
		.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE,
		.pad = 0,
		.freq = 20 * 1000 * 1000,
	};

	SpiInit(WIFI_IOT_SPI_ID_0, spi_init, &spi_cfg);
	SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 1);
}

void hspi_write(void *buf, uint32_t len)
{
	uint32_t ret;
	ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, buf, len);
	if (ret != WIFI_IOT_SUCCESS)
	{
		printf("[E][%s]SpiHostWrite failed: %d\n", TAG, ret);
	}
}
