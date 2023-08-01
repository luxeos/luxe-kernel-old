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
#define BLOCKS_PER_BYTE 8

void bitmap_set(uint64_t bit);
void bitmap_clear(uint64_t bit);
uint8_t bitmap_test(uint64_t bit);

void bitmap_set_range(uint64_t addr, uint64_t blocks);
void bitmap_clear_range(uint64_t addr, uint64_t blocks);
uint8_t bitmap_test_range(uint64_t addr, uint64_t blocks);

void phys_init();

uint64_t phys_alloc(uint64_t addr, uint64_t size);
void phys_free(uint64_t addr, uint64_t size);

void _phys_alloc_region(uint64_t base, uint64_t size);
uint64_t *_phys_alloc_range(uint64_t addr, uint64_t size);
char *_phys_get_type(uint64_t type);

#endif /* __PHYS_H_ */