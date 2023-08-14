/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <int/idt.h>
#include <dd/apic/apic.h>
#include <dd/apic/pic.h>
#include <cpu/cpu.h>
#include <panic.h>

#include <luxe.h>

idt_t idt[IDT_MAX_ENTRIES];

extern uintptr_t int_vector_table[];

void idt_init()
{
	for (size_t i = 0; i < 256; i++) {
		idt_set_entry(i, (uint64_t)int_vector_table[i], 0x8E);
	}

	pic_remap();

	idtr_t idtr;
	idtr.limit = sizeof(idt) - 1;
	idtr.base = (uint64_t)&idt;
	_idt_load(&idtr);

	klog("done");
}

void idt_set_entry(uint8_t vector, uint64_t handler, uint8_t flags)
{
	idt_t *entry = &idt[vector];

	entry->addr_low = handler & 0xFFFF;
	entry->selector = 0x08; // kernel cs
	entry->ist = 0;
	entry->flags = flags;
	entry->addr_mid = (handler >> 16) & 0xFFFF;
	entry->addr_upper = handler >> 32;
	entry->reserved = 0;
}

void int_handler(uint64_t rsp)
{
	cpu_regs_t *context = (cpu_regs_t *)rsp;

	if (context->vector < 0x20) {
		wizard_show();
		_klog("Vector 0x%.2x, Error 0x%x, CR2 0x%x\n", context->vector,
			  context->error, read_cr2());
		_klog("Stack trace:\n");
		backtrace();
		_klog("End of trace. System halted.\n");

		for (;;) {
			__asm__("hlt");
		}
	} else {
		klog("TICK");
		apic_eoi();
	}
}