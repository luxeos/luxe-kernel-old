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

#include <dd/fb/fb.h>
#include <debug/klog.h>
#include <dd/uart/uart.h>

#include "printf.h"

#include <luxe.h>

lock_t klog_lock;

void _klog(char *fmt, ...)
{
	lock_acquire(&klog_lock);

	va_list ptr;
	char klog_buffer[4096];

	va_start(ptr, fmt);
	vsnprintf((char *)&klog_buffer, -1, fmt, ptr);
#ifndef CONFIG_DEBUG
	// if (g_fb_init && boot_parse_cmdline("-v")) {
	if (g_fb_init) {
		fb_write(klog_buffer);
	}
	// }
#else
	uart_write(klog_buffer);
#endif
	va_end(ptr);

	lock_release(&klog_lock);
}