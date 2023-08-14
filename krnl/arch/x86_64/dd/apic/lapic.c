/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <dd/apic/lapic.h>
#include <acpi/madt.h>
#include <mem/mmio.h>

#include <luxe.h>

void lapic_init()
{
	lapic_out(0x80, 0);
	lapic_out(0xe0, 0xffffffff);
	lapic_out(0xd0, 0x01000000);
	lapic_out(0xf0, 0x100 | 0xff);

	klog("done");
}

uint32_t lapic_in(uint16_t reg)
{
	return mmio_read(get_lapic_addr() + reg);
}

void lapic_out(uint16_t reg, uint32_t value)
{
	mmio_write(get_lapic_addr() + reg, value);
}