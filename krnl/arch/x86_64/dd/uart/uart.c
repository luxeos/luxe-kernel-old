/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <dd/uart/uart.h>

#include <luxe.h>

luxe_status_t uart_init()
{
	outb(COM1 + 1, 0x00);
	outb(COM1 + 3, 0x80);
	outb(COM1, 0x03);
	outb(COM1 + 1, 0x00);
	outb(COM1 + 3, 0x03);
	outb(COM1 + 2, 0xC7);
	outb(COM1 + 4, 0x0B);
	outb(COM1 + 4, 0x0F);

	return luxe_success;
}

char uart_read()
{
	while ((inb(COM1 + 5) & 0x01) == 0);
	return inb(COM1);
}

void uart_write(char *str)
{
	while (*str) {
		while ((inb(COM1 + 5) & 0x20) == 0);
		outb(COM1, *str++);
	}
}