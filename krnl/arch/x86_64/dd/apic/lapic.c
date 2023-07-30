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
#include <dd/apic/pic.h>
#include <mem/mmio.h>

#include <luxe.h>

uint64_t *lapic_base;

void lapic_init()
{
	pic_disable();

	lapic_base = (uint64_t *)rdmsr(IA32_APIC_BASE);

	// klog("apic ver 0x%8x", mmio_read(APIC_REG_VER));
}