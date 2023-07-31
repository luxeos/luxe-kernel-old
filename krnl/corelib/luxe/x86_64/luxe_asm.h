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

static inline void outb(uint16_t port, uint8_t value)
{
	__asm__ volatile("outb %0, %1" :: "a"(value), "Nd"(port) : "memory");
}

static inline uint8_t inb(uint16_t port)
{
	uint8_t retval;
	__asm__ volatile("inb %1, %0" : "=a"(retval) : "Nd"(port) : "memory");
	return retval;
}

static inline void wrmsr(uint64_t msr, uint64_t value)
{
	uint32_t lower = value & 0xFFFFFFFF;
	uint32_t upper = value >> 32;
	__asm__ volatile("wrmsr" :: "c"(msr), "a"(lower), "d"(upper));
}

static inline uint64_t rdmsr(uint64_t msr)
{
	uint32_t lower, upper;
	__asm__ volatile("rdmsr" : "=a"(lower), "=d"(upper) : "c"(msr));
	return (((uint64_t)upper << 32) | lower);
}

static inline uint64_t read_cr2()
{
	uint64_t cr2;
	__asm__ volatile("mov %%cr2, %0" : "=a"(cr2));
	return cr2;
}

#endif /* __LUXE_ASM_H_ */