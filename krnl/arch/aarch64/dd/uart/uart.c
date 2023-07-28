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
#include <cpu/io.h>

#include <luxe.h>

volatile uint8_t __attribute__((aligned(0x10))) mbox[9] = {
	9*4, 0, 0x38002, 12, 8, 2, 3000000, 0, 0
};

luxe_status_t uart_init()
{
	mmio_out(UART0_CR, 0);
	mmio_out(GPPUD, 0);
	delay(150);

	mmio_out(GPPUDCLK0, (1 << 14) | (1 << 15));
	delay(150);

	mmio_out(GPPUDCLK0, 0);
	mmio_out(UART0_ICR, 0x7FF);

	uint8_t r = (((uint8_t)(&mbox) & ~0xF) | 8);
	while (mmio_in(MBOX_STATUS) & 0x80000000);
	mmio_out(MBOX_WRITE, r);
	while ((mmio_in(MBOX_STATUS) & 0x40000000) || mmio_in(MBOX_READ) != r);

	mmio_out(UART0_IBRD, 1);
	mmio_out(UART0_FBRD, 40);
	mmio_out(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));
	mmio_out(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5 | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10)));
	mmio_out(UART0_CR, 1 | (1 << 8) | (1 << 9));

	return luxe_success;
}

void _uart_write(char s)
{
	while (!(mmio_in(UART0_FR) & (1 << 5)));
	mmio_out(UART0_DR, s);
}

void uart_write(char *str)
{
	while (*str) {
		if (*str == '\n') _uart_write('\r');
		_uart_write(*str++);
	}
}