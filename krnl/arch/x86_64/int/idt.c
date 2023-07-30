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
#include <dd/pic/pic.h>
#include <cpu/cpu.h>

#include <luxe.h>

idt_t idt[IDT_MAX_ENTRIES];

extern uintptr_t int_vector_table[];

void idt_init()
{
	for (size_t i = 0; i < 48; i++) {
		idt_set_entry(i, (uint64_t)int_vector_table[i], 0x8E);
	}

	pic_remap();

	idtr_t idtr;
	idtr.limit = sizeof(idt) - 1;
	idtr.base = (uint64_t)&idt;
	(void)idtr;
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

uint64_t int_handler(uint64_t rsp)
{
	cpu_regs_t *context = (cpu_regs_t *)rsp;
	
	if (context->vector <= 0x20) {
		_klog("                         /\\\n");
		_klog("                        /  \\\n");
		_klog("                       |    |\n");
		_klog("                     --:'''':--\n");
		_klog("                       :'_' :\n");
		_klog("                       _:"":\\___\n");
		_klog("        ' '      ____.' :::     '._\n");
		_klog("       . *=====<<=)           \\    :\n");
		_klog("        .  '      '-'-'\\_      /'._.'\n");
		_klog("                         \\====:_ ""\n");
		_klog("                        .'     \\\\\n");
		_klog("                       :       :\n");
		_klog("                      /   :    \\\n");
		_klog("                     :   .      '.\n");
		_klog("                     :  : :      :\n");
		_klog("                     :__:-:__.;--'\n");
		_klog("                     '-'   '-'\n");
		_klog("    You have been visited by the mighty wizard.\n");
		_klog("  A fatal error occured, and the computer cannot function properly anymore.\n");
		_klog("  Please send the following to the developers:\n\n");

		_klog("Vector 0x%.2x, Error 0x%x\n", context->vector, context->error);

		_klog("Stack trace:\n");
		backtrace(context->rbp);
	}

	for (;;) {
		__asm__("hlt");
	}
	return rsp;
}