/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <dd/apic/ioapic.h>
#include <acpi/madt.h>
#include <mem/mmio.h>

#include <luxe.h>

void ioapic_init()
{
	uint32_t entries_count = ioapic_in(IOAPICVER);
	uint32_t count = ((entries_count >> 16) & 0xff) + 1;
	klog("%d ioapic pins", count);

	for (uint32_t i = 0; i < count; ++i) {
		ioapic_set_entry(i, 1 << 16);
	}

	klog("done");
}

void ioapic_set_entry(uint8_t index, uint64_t data)
{
	ioapic_out(IOREDTBL + index * 2, (uint32_t)data);
	ioapic_out(IOREDTBL + index * 2 + 1, (uint32_t)(data >> 32));
}

uint32_t ioapic_in(uint8_t reg)
{
	mmio_write(get_ioapic_addr() + IOREGSEL, reg);
	return mmio_read(get_ioapic_addr() + IOWIN);
}

void ioapic_out(uint8_t reg, uint32_t value)
{
	mmio_write(get_ioapic_addr() + IOREGSEL, reg);
	mmio_write(get_ioapic_addr() + IOWIN, value);
}