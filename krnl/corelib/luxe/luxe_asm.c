/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <stdint.h>
#include <luxe.h>

void outb(uint16_t port, uint8_t value)
{
	__asm__ volatile("outb %0, %1" :: "a"(value), "Nd"(port) : "memory");
}

uint8_t inb(uint16_t port)
{
	uint8_t retval;
	__asm__ volatile("inb %1, %0" : "=a"(retval) : "Nd"(port) : "memory");
	return retval;
}