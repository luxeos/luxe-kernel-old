/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <dd/fb/fb.h>
#include <debug/klog.h>
#include <dd/uart/uart.h>

#include "printf.h"

void _klog(char *fmt, ...)
{
#ifndef CONFIG_DEBUG
	va_list ptr;
	char klog_buffer[4096];

	va_start(ptr, fmt);
	vsnprintf((char *)&klog_buffer, -1, fmt, ptr);
	if (g_fb_init) {
		fb_write(klog_buffer);
	}
	va_end(ptr);
#else
	va_list ptr;
	char klog_buffer[4096];

	va_start(ptr, fmt);
	vsnprintf((char *)&klog_buffer, -1, fmt, ptr);
	uart_write(klog_buffer);
	va_end(ptr);
#endif
}