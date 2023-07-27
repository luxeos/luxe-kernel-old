/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#ifndef __SERIAL_H_
#define __SERIAL_H_

#include <luxe.h>

#define COM1 0x3F8

luxe_status_t serial_init();

char serial_read();
void serial_write(char *str);

#endif /* __SERIAL_H_ */