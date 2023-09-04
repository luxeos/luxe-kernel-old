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
#include <dd/apic/apic.h>
#include <dd/apic/lapic.h>
#include <mem/mmio.h>
#include <mem/phys.h>
#include <mem/virt.h>

#include <luxe.h>

void lapic_init(void)
{
	virt_map(NULL, (uint64_t)g_lapic_addr, VIRT_TO_PHYS(g_lapic_addr), 1,
			 VIRT_FLAGS_MMIO);

	_lapic_out(LAPIC_TPR, 0);
	_lapic_out(LAPIC_DFR, 0xffffffff);
	_lapic_out(LAPIC_LDR, 0x01000000);
	_lapic_out(LAPIC_SVR, 0x100 | 0xff);

	klog("done");
}

uint32_t lapic_get_id(void)
{
	return _lapic_in(LAPIC_ID) >> 24;
}

void lapic_send_init(uint32_t apic_id)
{
	(void)apic_id;
	klog("NOT IMPLEMENTED YET");
}

void lapic_send_startup(uint32_t apic_id, uint32_t vector)
{
	(void)apic_id;
	(void)vector;
	klog("NOT IMPLEMENTED YET");
}

uint32_t _lapic_in(uint16_t reg)
{
	return mmio_read((void *)(g_lapic_addr + reg));
}

void _lapic_out(uint16_t reg, uint32_t value)
{
	mmio_write((void *)(g_lapic_addr + reg), value);
}