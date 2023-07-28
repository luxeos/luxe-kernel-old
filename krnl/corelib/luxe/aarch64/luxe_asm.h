/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#ifndef __LUXE_ASM_H_
#define __LUXE_ASM_H_

#include <stdint.h>

static inline void delay(int32_t count)
{
	__asm__ volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=" : "=r"(count) : [count]"0"(count) : "cc");
}

#endif /* __LUXE_ASM_H_ */