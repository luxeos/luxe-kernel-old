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
#include <luxe.h>

void kernel_init(void)
{
	arch_init();

	__asm__("int $0x00");

	klog("Welcome to LuxeOS");
	for (;;);
}