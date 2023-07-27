/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <boot/boot.h>
#include <dd/serial/serial.h>

#include <luxe.h>

void kernel_init(void)
{
	serial_init();
	serial_write("Welcome to LuxeOS");

	for (;;);
}