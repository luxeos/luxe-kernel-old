/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <cpu/gdt.h>

#include <luxe.h>

// 5 entries for the GDT itself
// 2 entries for the TSS
#define GDT_ENTRIES 5 + 2

gdt_t gdt[GDT_ENTRIES];
tss_t tss;

void gdt_init()
{
	gdt_set_entry(0, 0, 0, 0, 0); // = null descriptor
	gdt_set_entry(1, 0, 0xfffff, 0x9A, 0x02); // = kernel cs
	gdt_set_entry(2, 0, 0xfffff, 0x92, 0x02); // = kernel ds
	gdt_set_entry(3, 0, 0xfffff, 0xFA, 0x02); // = user cs
	gdt_set_entry(4, 0, 0xfffff, 0xF2, 0x02); // = user ds

	// TSS
	gdt_set_entry(5, (uintptr_t)(&tss) & 0xffffffff, sizeof(tss_t) - 1, 0x89,
				  0x40);

	gdtr_t gdtr;
	gdtr.size = sizeof(gdt) - 1;
	gdtr.offset = (uint64_t)&gdt;
	_gdt_load(&gdtr);

	klog("done");
}

void gdt_set_entry(int entry, uint32_t base, uint32_t limit, uint8_t access,
				   uint8_t flags)
{
	if (entry >= GDT_ENTRIES) {
		klog("Wanted to write entry %i, but GDT has %i entries total.",
			 entry + 1, GDT_ENTRIES);
		for (;;) {
			__asm__("hlt");
		}
	}

	gdt[entry].limit_low = (limit >> 8) & 0xff;
	gdt[entry].base_low = (base >> 8) & 0xff;
	gdt[entry].base_mid = (base >> 16) & 0xff;
	gdt[entry].access = access;
	gdt[entry].limit_hi = (limit >> 16) & 0xf;
	gdt[entry].flags = flags;
	gdt[entry].base_hi = (base >> 24) & 0xff;
}