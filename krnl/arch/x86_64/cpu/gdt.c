/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <luxe.h>
#include <stdint.h>

__attribute__((aligned(0x1000))) gdt_t gdt[GDT_ENTRIES];

void gdt_init()
{
	gdt_set_entry(0, 0, 0, 0, 0); // = null descriptor
	gdt_set_entry(1, 0, 0, 0x9A, 0xA0); // = kernel cs
	gdt_set_entry(2, 0, 0, 0x92, 0xC0); // = kernel ds
	gdt_set_entry(3, 0, 0, 0xFA, 0xA0); // = user cs
	gdt_set_entry(4, 0, 0, 0xF2, 0xC0); // = user ds

	gdtr_t gdtr;
	gdtr.size = sizeof(gdt) - 1;
	gdtr.offset = (uint64_t)&gdt;
	_gdt_load(&gdtr);

	klog("done");
}

void gdt_set_entry(int entry, uint16_t limit_low, uint32_t base, uint8_t access,
				   uint8_t limit_flags)
{
	if (entry >= GDT_ENTRIES) {
		klog("Wanted to write entry %i, but GDT has %i entries total.",
			 entry + 1, GDT_ENTRIES);
		for (;;) {
			__asm__("hlt");
		}
	}

	gdt[entry].limit_low = limit_low;
	gdt[entry].base_low = (base >> 8) & 0xFF;
	gdt[entry].base_mid = (base >> 16) & 0xFF;
	gdt[entry].access = access;
	gdt[entry].limit_flags = limit_flags;
	gdt[entry].base_upper = (base >> 24) & 0xFF;
}