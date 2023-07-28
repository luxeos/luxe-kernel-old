#ifndef __IO_H_
#define __IO_H_

#include <luxe.h>

#define MMIO_BASE 0xFE000000

#define GPIO_BASE (MMIO_BASE + 0x200000)
#define GPPUD (GPIO_BASE + 0x94)
#define GPPUDCLK0 (GPIO_BASE + 0x98)

void mmio_out(uint32_t reg, uint32_t val);
uint32_t mmio_in(uint32_t reg);

#endif /* __IO_H_ */