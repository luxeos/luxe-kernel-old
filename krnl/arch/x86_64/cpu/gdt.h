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

typedef struct {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t limit_hi : 4;
	uint8_t flags : 4;
	uint8_t base_hi;
} __attribute__((packed)) gdt_t;

typedef struct {
	uint32_t reserved0;
	uint64_t rsp0;
	uint64_t rsp1;
	uint64_t rsp2;
	uint64_t reserved1;
	uint64_t ist[7];
	uint64_t reserved2;
	uint16_t reserved3;
	uint16_t iopb;
} __attribute__((packed)) tss_t;

typedef struct {
	uint16_t size;
	uint64_t offset;
} __attribute__((packed)) gdtr_t;

void gdt_init(void);
void gdt_set_entry(int entry, uint32_t base, uint32_t limit, uint8_t access,
				   uint8_t flags);

extern void _gdt_load(gdtr_t *gdtr);

#endif /* __GDT_H_ */