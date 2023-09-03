/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <acpi/acpi.h>
#include <boot/bootlogo.h>
#include <cpu/gdt.h>
#include <int/idt.h>
#include <dd/uart/uart.h>
#include <dd/fb/fb.h>
#include <mem/phys.h>
#include <mem/virt.h>

#include <luxe.h>

void arch_init()
{
	uart_init();

	gdt_init();
	idt_init();

	fb_init();
	display_bootlogo();

	phys_init();
	virt_init();

	acpi_init();
}