/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <cpu/gdt.h>
#include <int/idt.h>
#include <dd/uart/uart.h>
#include <mem/phys.h>
#include <mem/virt.h>

#include <luxe.h>

void arch_init()
{
	uart_init();

	gdt_init();
	idt_init();

	phys_init();
	virt_init();
}