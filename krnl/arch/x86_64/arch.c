/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <luxe.h>

#include <acpi/acpi.h>
#include <dd/apic/lapic.h>
#include <dd/uart/uart.h>
#include <cpu/gdt.h>
#include <mem/phys.h>
#include <int/idt.h>

void arch_init()
{
	uart_init();

	gdt_init();
	idt_init();

	acpi_init();

	phys_init();

	lapic_init();
}