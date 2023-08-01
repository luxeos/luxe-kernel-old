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
#include <mem/phys.h>
#include <stdint.h>

#include "luxe_malloc.h"

void *kmalloc(uint64_t size)
{
	struct limine_hhdm_response *hhdm = hhdm_request.response;

	if (size <= 0) {
		klog("cannot allocate memory of size < 0 (%i)", size);
		return NULL;
	}

	memalloc_attr_t *attributes =
		(memalloc_attr_t *)(phys_alloc(0, size + 1) + hhdm->offset);
	attributes->blocks = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;
	attributes->size = size;

	return (void *)(attributes + BLOCK_SIZE);
}

void kfree(void *addr)
{
	struct limine_hhdm_response *hhdm = hhdm_request.response;
	memalloc_attr_t *attributes =
		(memalloc_attr_t *)((uint64_t *)addr - BLOCK_SIZE);

	phys_free((uint64_t)addr - hhdm->offset, attributes->blocks + 1);
}

void krealloc(void *addr, uint64_t size)
{
	(void)addr;
	(void)size;
}