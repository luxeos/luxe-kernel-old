/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#ifndef __GDT_H_
#define __GDT_H_

#include <luxe.h>
#include <stdint.h>

#define GDT_ENTRIES 5

typedef struct {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t limit_flags;
	uint8_t base_upper;
} __attribute__((packed)) gdt_t;

typedef struct {
	uint16_t size;
	uint64_t offset;
} __attribute__((packed)) gdtr_t;

void gdt_init();

void gdt_set_entry(int entry, uint16_t limit_low, uint32_t base, uint8_t access,
				   uint8_t limit_flags);
extern void _gdt_load(gdtr_t *gdtr);

#endif /* __GDT_H_ */