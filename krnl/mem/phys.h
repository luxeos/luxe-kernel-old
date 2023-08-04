/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#ifndef __PHYS_H_
#define __PHYS_H_

#include <luxe.h>

#define BLOCK_SIZE 4096
#define BLOCKS_PER_BYTE 64

#define ALIGN_UP(addr, align) (((addr) + (align) - 1) & ~((align) - 1))
#define ALIGN_DOWN(addr, align) ((addr) & ~((align) - 1))

#define NUM_BLOCKS(size) (((size) * 1024) / BLOCK_SIZE)

#define KERNEL_VIRT_TO_PHYS(addr) (((uint64_t)(addr)) - 0xFFFFFFFF80000000UL)
#define KERNEL_PHYS_TO_VIRT(addr) (((uint64_t)(addr)) + 0xFFFFFFFF80000000UL)
#define DATA_VIRT_TO_PHYS(addr) (((uint64_t)(addr)) - hhdm_request.response->offset)
#define DATA_PHYS_TO_VIRT(addr) (((uint64_t)(addr)) + hhdm_request.response->offset)

void bitmap_set(uint64_t bit);
void bitmap_clear(uint64_t bit);
uint64_t bitmap_test(uint64_t bit);

void phys_init();

void *phys_alloc(uint64_t block_num);
void *phys_allocz(uint64_t block_num);
void phys_free(void *ptr, size_t block_num);

void *_phys_find_free_range(uint64_t block_num);
char *_phys_get_type(uint64_t type);

#endif /* __PHYS_H_ */