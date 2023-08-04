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
#include <luxe.h>

static uint64_t *g_bitmap = NULL;

uint64_t g_highest_block = 0;
uint64_t g_used_blocks = 0;

void bitmap_set(uint64_t bit)
{
	g_bitmap[bit / BLOCKS_PER_BYTE] |= (1 << (bit % BLOCKS_PER_BYTE));
}

void bitmap_clear(uint64_t bit)
{
	g_bitmap[bit / BLOCKS_PER_BYTE] &= ~(1 << (bit % BLOCKS_PER_BYTE));
}

uint64_t bitmap_test(uint64_t bit)
{
	return g_bitmap[bit / BLOCKS_PER_BYTE] & (1 << (bit % BLOCKS_PER_BYTE));
}

void phys_init()
{
	struct limine_memmap_response *mmap = memmap_request.response;

	for (uint64_t i = 0; i < mmap->entry_count; i++) {
		struct limine_memmap_entry *entry = mmap->entries[i];

		klog("entry %i, base 0x%lx, length 0x%lx, type %s", i, entry->base,
			 entry->length, _phys_get_type(entry->type));
		
		if (entry->type != LIMINE_MEMMAP_USABLE &&
			entry->type != LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE &&
			entry->type != LIMINE_MEMMAP_KERNEL_AND_MODULES) {
				continue;
			}
		
		if ((entry->base + entry->length) > g_highest_block) {
			g_highest_block = (entry->base + entry->length);
		}
	}

	g_used_blocks = NUM_BLOCKS(g_highest_block);

	uint64_t bitmap_size = ALIGN_UP(ALIGN_DOWN(g_highest_block, BLOCK_SIZE) / BLOCK_SIZE / 8, BLOCK_SIZE);

	// map bitmap
	for (uint64_t i = 0; i < mmap->entry_count; i++) {
		struct limine_memmap_entry *entry = mmap->entries[i];

		if (entry->type != LIMINE_MEMMAP_USABLE) {
			continue;
		}

		if (entry->length >= bitmap_size) {
			g_bitmap = (uint64_t *)DATA_PHYS_TO_VIRT(entry->base);
			entry->base += bitmap_size;
			entry->length -= bitmap_size;

			klog("stored bitmap at 0x%lx", entry->base);
			break;
		}
	}

	memset((void *)g_bitmap, 0xFF, bitmap_size);
	for (uint64_t i = 0; i < mmap->entry_count; i++) {
		struct limine_memmap_entry *entry = mmap->entries[i];

		if (entry->type == LIMINE_MEMMAP_USABLE) {
			phys_free((void *)entry->base, entry->length / BLOCK_SIZE);
		}
	}

	bitmap_set(0);
	klog("done");
}

void *phys_alloc(uint64_t block_num)
{
	if (g_used_blocks <= 0) {
		// out of memory
		panic();
	}

	void *ptr = _phys_find_free_range(block_num);
	if (ptr == NULL) {
		return NULL;
	}

	uint64_t index = ((uint64_t)ptr / BLOCK_SIZE);
	for (uint64_t i = 0; i < block_num; i++) {
		bitmap_set(index + i);
	}
	
	g_used_blocks += block_num;
	return (void *)(index * BLOCK_SIZE);
}

void *phys_allocz(uint64_t block_num)
{
	void *ptr = phys_alloc(block_num);
	memset(ptr, 0, BLOCK_SIZE * block_num);

	return ptr;
}

void phys_free(void *ptr, size_t block_num)
{
	uint64_t index = (uint64_t)ptr / BLOCK_SIZE;

	for (size_t i = 0; i < block_num; i++) {
		bitmap_clear(index + i);
	}

	g_used_blocks -= block_num;
}

void *_phys_find_free_range(uint64_t block_num)
{
	for (uint64_t bits = 0; bits < (g_highest_block / BLOCK_SIZE); bits++) {
		for (uint64_t blocks = 0; blocks < block_num; block_num++) {
			if (bitmap_test(bits + (blocks / BLOCK_SIZE))) {
				break;
			}

			if (blocks == block_num - 1) {
				return (void *)(bits * BLOCK_SIZE);
			}
		}
	}

	return NULL;
}

char *_phys_get_type(uint64_t type)
{
	switch (type) {
	case LIMINE_MEMMAP_USABLE:
		return "Usable";
	case LIMINE_MEMMAP_RESERVED:
		return "Reserved";
	case LIMINE_MEMMAP_ACPI_RECLAIMABLE:
		return "ACPI Reclaimable";
	case LIMINE_MEMMAP_ACPI_NVS:
		return "ACPI NVS";
	case LIMINE_MEMMAP_BAD_MEMORY:
		return "Bad Memory";
	case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
		return "Bootloader Reclaimable";
	case LIMINE_MEMMAP_KERNEL_AND_MODULES:
		return "Kernel and Modules";
	case LIMINE_MEMMAP_FRAMEBUFFER:
		return "Framebuffer";
	default:
		return "???";
	}
}