#ifndef _RETRPL_HSPI_
#define _RETRPL_HSPI_

#include <stdint.h>

void hspi_init(void);
void hspi_write(void *buf, uint32_t len);

#endif // _RETRPL_HSPI_
