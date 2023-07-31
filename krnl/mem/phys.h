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

#define PAGE_SIZE 4096

void bitmap_set(uint8_t bit);
void bitmap_clear(uint8_t bit);
uint8_t bitmap_test(uint8_t bit);

void phys_init();

char *_phys_get_type(uint64_t type);

#endif /* __PHYS_H_ */