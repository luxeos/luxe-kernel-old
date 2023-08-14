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

#define BLOCK_SIZE 0x1000
#define BLOCKS_PER_BYTE 64

#define NUM_BLOCKS(num) (((num) + BLOCK_SIZE - 1) / BLOCK_SIZE)

#define MEM_VIRT_OFF hhdm_request.response->offset
#define VIRT_TO_PHYS(a) ((uint64_t)(a)-MEM_VIRT_OFF)
#define PHYS_TO_VIRT(a) ((uint64_t)(a) + MEM_VIRT_OFF)

void bitmap_set(uint64_t addr, uint64_t blocks);
void bitmap_clear(uint64_t addr, uint64_t blocks);
bool bitmap_test(uint64_t addr, uint64_t blocks);

void phys_init();

uint64_t phys_alloc(uint64_t base, uint64_t blocks);
void phys_free(uint64_t addr, uint64_t blocks);

uint64_t phys_get_total_memory();
uint64_t phys_get_free_memory();
uint64_t phys_get_highest_block();

bool _phys_is_addr_free(uint64_t addr, uint64_t blocks);
char *_phys_get_type(uint64_t type);

#endif /* __PHYS_H_ */