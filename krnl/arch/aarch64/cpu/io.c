/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <cpu/io.h>
#include <luxe.h>

void mmio_out(uint32_t reg, uint32_t val)
{
	*(volatile uint32_t *)(MMIO_BASE + reg) = val;
}

uint32_t mmio_in(uint32_t reg)
{
	return *(volatile uint32_t *)(MMIO_BASE + reg);
}