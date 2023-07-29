/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#ifndef __IDT_H_
#define __IDT_H_

#include <cpu/cpu.h>

#include <luxe.h>

#define IDT_MAX_ENTRIES 256

typedef struct {
	uint16_t addr_low; // 0:15 handler
	uint16_t selector; // kernel cs
	uint8_t ist; // always zero for now
	uint8_t flags;
	uint16_t addr_mid; // 16:31 handler
	uint32_t addr_upper; // 32:63 handler
	uint32_t reserved; // always zero
} __attribute__((packed)) idt_t;

typedef struct {
	uint16_t limit;
	uint64_t base;
} __attribute__((packed)) idtr_t;

void idt_init();
void idt_set_entry(uint8_t vector, uint64_t handler, uint8_t flags);

uint64_t int_handler(uint64_t rsp);

extern void _idt_load(idtr_t *idtr);

#endif /* __IDT_H_ */