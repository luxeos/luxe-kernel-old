/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <acpi/madt.h>
#include <int/irq.h>
#include <dd/apic/apic.h>
#include <dd/apic/lapic.h>
#include <dd/apic/ioapic.h>
#include <dd/apic/pic.h>
#include <dd/pit/pit.h>
#include <int/idt.h>
#include <mem/mmio.h>
#include <mem/phys.h>
#include <mem/virt.h>

#include <luxe.h>

void apic_init()
{
	pic_disable();

	virt_map(NULL, get_lapic_addr(), VIRT_TO_PHYS(get_lapic_addr()), 1,
			 VIRT_FLAGS_MMIO, true);
	virt_map(NULL, get_ioapic_addr(), VIRT_TO_PHYS(get_ioapic_addr()), 1,
			 VIRT_FLAGS_MMIO, true);

	lapic_init();
	ioapic_init();

	// 11th bit of IA32_APIC_BASE_MSR
	uint64_t msr = rdmsr(0x1b);
	msr |= (1 << 11);
	wrmsr(0x1b, msr);

	// enable irqs
	ioapic_set_entry(apic_get_irq(0), PIC_REMAP_OFFSET);

	// register handlers
	irq_register(0, pit_tick);

	sti();
	klog("done");
}

void apic_eoi()
{
	lapic_out(0xb0, 0);
}

uint8_t apic_get_irq(uint8_t irq)
{
	for (int i = 0; i < 16; i++) {
		apic_iso_t *iso = get_ioapic_iso(i);
		if (iso->irq == irq) {
			klog("found iso for irq %i, returning %i", irq, iso->gsi);
			return iso->gsi;
		}
	}

	return irq;
}