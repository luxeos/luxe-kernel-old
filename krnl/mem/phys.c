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

static uint64_t g_total_mem = 0;
static uint64_t g_max_blocks = 0;
static uint64_t g_used_blocks = 0;

void bitmap_set(uint64_t bit)
{
	g_bitmap[bit / 64] |= (1 << (bit % 64));
}

void bitmap_clear(uint64_t bit)
{
	g_bitmap[bit / 64] &= ~(1 << (bit % 64));
}

uint8_t bitmap_test(uint64_t bit)
{
	return g_bitmap[bit / 64] & (1 << (bit % 64));
}

void phys_init()
{
	struct limine_memmap_response *mmap = memmap_request.response;
    struct limine_hhdm_response *hhdm = hhdm_request.response;

	uint64_t highest_addr = 0;

	for (size_t i = 0; i < mmap->entry_count; i++) {
		struct limine_memmap_entry *entry = mmap->entries[i];

		klog("entry %i, base 0x%lx, length 0x%lx, type %s", i, entry->base, entry->length, _phys_get_type(entry->type));

		if (entry->type == LIMINE_MEMMAP_USABLE ||
			entry->type == LIMINE_MEMMAP_ACPI_RECLAIMABLE ||
			entry->type == LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE) {
				g_total_mem += entry->length;
				g_max_blocks += ROUND_UP(entry->length, BLOCK_SIZE);
				highest_addr = MAX(highest_addr, entry->base + entry->length);
			}
	}

	uint64_t bitmap_size = ALIGN_UP((highest_addr / BLOCK_SIZE) / BLOCKS_PER_BYTE, BLOCK_SIZE);
	g_used_blocks = g_max_blocks;

	for (size_t i = 0; i < mmap->entry_count; i++) {
		struct limine_memmap_entry *entry = mmap->entries[i];
		
		if (entry->type != LIMINE_MEMMAP_USABLE) {
				continue;
			}
		
		if (entry->length >= bitmap_size) {
			g_bitmap = (uint64_t *)(entry->base + hhdm->offset);
			
			memset(g_bitmap, 0xFF, g_max_blocks / BLOCKS_PER_BYTE);
			
			entry->length -= bitmap_size;
			entry->base += bitmap_size;
			break;
		}
	}

	for (size_t i = 0; i < mmap->entry_count; i++) {
		struct limine_memmap_entry *entry = mmap->entries[i];
		if (entry->type != LIMINE_MEMMAP_USABLE) {
				continue;
			}
		_phys_free_region(entry->base, entry->length);
	}

	klog("Total memory: %llu MiB", (g_max_blocks * BLOCK_SIZE) / 1024 / 1024);
	klog("Used memory: %llu MiB", (g_used_blocks * BLOCK_SIZE) / 1024 / 1024);
}

uint64_t *phys_alloc(uint64_t blocks)
{
	if ((g_max_blocks - g_used_blocks) <= blocks) {
		return NULL;
	}

	int64_t start_block = _phys_find_free_blocks(blocks);
	if (start_block == -255) {
		klog("not enough memory for %i blocks, returning null.", blocks);
		return NULL;
	}

	for (uint64_t i = 0; i < blocks; i++) {
		bitmap_set(start_block + i);
	}

	g_used_blocks += blocks;
	uint64_t address = start_block * BLOCK_SIZE;
	
	klog("allocated %i blocks at 0x%x", blocks, start_block);
	return (uint64_t *)address;
}

void phys_free(uint64_t *address, uint64_t blocks)
{
	int64_t start_block = (uint64_t)address / BLOCK_SIZE;

	for (uint64_t i = 0; i < blocks; i++) {
		bitmap_clear(start_block + i);
	}

	g_used_blocks -= blocks;
	klog("freed %i blocks from 0x%x", blocks, address);
}

void _phys_alloc_region(uint64_t base, uint64_t size)
{
	uint64_t align = base / BLOCK_SIZE;
	uint64_t blocks = size / BLOCK_SIZE;

	for (; blocks > 0; blocks--) {
		bitmap_set(align++);
		g_used_blocks++;
	}

	klog("allocated %i blocks at 0x%x", (size / BLOCK_SIZE), base);
}

void _phys_free_region(uint64_t base, uint64_t size)
{
	uint64_t align = base / BLOCK_SIZE;
	uint64_t blocks = size / BLOCK_SIZE;

	for (; blocks > 0; blocks--) {
		bitmap_clear(align++);
		g_used_blocks--;
	}

	bitmap_set(0);
	klog("freed %i blocks at 0x%x", (size / BLOCK_SIZE), base);
}

int64_t _phys_find_free_blocks(uint64_t blocks)
{
	if (blocks == 0)
		return -255;
	
	for (uint64_t i = 0; i < g_max_blocks / 64; i++) {
		if (g_bitmap[i] != 0xFFFFFFFFFFFFFFFF) {
			// find which bit is not set
			for (int64_t j = 0; j < 64; j++) {
				int64_t bit = 1 << j;

				if (!(g_bitmap[i] & j)) {
					int64_t free_block_start = i * 64 + bit;
					uint64_t free_blocks = 0;

					for (uint64_t count = 0; count <= blocks; count++) {
						if (!bitmap_test(free_block_start + count)) {
							free_blocks++;

							if (free_blocks == blocks) {
								return i * 64 + j;
							}
						}
					}
				}
			}
		}
	}

	return -255;
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