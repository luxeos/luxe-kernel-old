#ifndef __PANIC_H_
#define __PANIC_H_

#include <cpu/cpu.h>

extern void panic(int err);

void __panic(cpu_regs_t regs, int err);

void luxeos_print_ver_str(void);

#endif /* __PANIC_H_ */