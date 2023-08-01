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
static uint64_t g_highest_addr = 0;

static uint64_t g_total_mem = 0;
static uint64_t g_free_mem = 0;

void bitmap_set(uint64_t bit)
{
	g_bitmap[bit / (BLOCK_SIZE * BLOCKS_PER_BYTE)] |=
		(1 << ((bit / BLOCK_SIZE) % BLOCKS_PER_BYTE));
}

void bitmap_clear(uint64_t bit)
{
	g_bitmap[bit / (BLOCK_SIZE * BLOCKS_PER_BYTE)] &=
		~(1 << ((bit / BLOCK_SIZE) % BLOCKS_PER_BYTE));
}

uint8_t bitmap_test(uint64_t bit)
{
	return g_bitmap[bit / (BLOCK_SIZE * BLOCKS_PER_BYTE)] &
		   (1 << ((bit / BLOCK_SIZE) % BLOCKS_PER_BYTE));
}

void bitmap_set_range(uint64_t addr, uint64_t blocks)
{
	for (uint64_t i = addr; i < addr + (blocks * BLOCK_SIZE); i += BLOCK_SIZE) {
		bitmap_set(i);
	}
}

void bitmap_clear_range(uint64_t addr, uint64_t blocks)
{
	for (uint64_t i = addr; i < addr + (blocks * BLOCK_SIZE); i += BLOCK_SIZE) {
		bitmap_clear(i);
	}
}

uint8_t bitmap_test_range(uint64_t addr, uint64_t blocks)
{
	for (uint64_t i = addr; i < addr + (blocks * BLOCK_SIZE); i += BLOCK_SIZE) {
		if (!bitmap_test(i)) {
			return 0;
		}
	}
	return 1;
}

void phys_init()
{
	struct limine_memmap_response *mmap = memmap_request.response;
	struct limine_hhdm_response *hhdm = hhdm_request.response;

	for (size_t i = 0; i < mmap->entry_count; i++) {
		struct limine_memmap_entry *entry = mmap->entries[i];

		klog("entry %i, base 0x%lx, length 0x%lx, type %s", i, entry->base,
			 entry->length, _phys_get_type(entry->type));

		if (entry->type == LIMINE_MEMMAP_USABLE ||
			entry->type == LIMINE_MEMMAP_ACPI_RECLAIMABLE ||
			entry->type == LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE ||
			entry->type == LIMINE_MEMMAP_KERNEL_AND_MODULES) {
			g_total_mem += entry->length;
		}

		if ((entry->base + entry->length) > g_highest_addr) {
			g_highest_addr = entry->base + entry->length;
		}
	}

	uint64_t bitmap_size = g_highest_addr / (BLOCK_SIZE * BLOCKS_PER_BYTE);

	for (size_t i = 0; i < mmap->entry_count; i++) {
		struct limine_memmap_entry *entry = mmap->entries[i];

		if (entry->type != LIMINE_MEMMAP_USABLE) {
			continue;
		}

		if (entry->base + entry->length <= 0x100000) {
			continue;
		}

		if (entry->length >= bitmap_size) {
			g_bitmap = (uint64_t *)(entry->base + hhdm->offset);
			memset(g_bitmap, 0, bitmap_size);
			_phys_alloc_range((uint64_t)entry->base, bitmap_size);

			klog("stored bitmap at 0x%lx", g_bitmap);
			break;
		}
	}

	for (size_t i = 0; i < mmap->entry_count; i++) {
		struct limine_memmap_entry *entry = mmap->entries[i];

		if (entry->base + entry->length <= 0x100000) {
			continue;
		}

		if (entry->type == LIMINE_MEMMAP_USABLE) {
			phys_free(entry->base, entry->length);
			continue;
		}
	}

	klog("Total memory: %llu MiB", g_total_mem / 1024 / 1024);
	klog("Used memory: %llu MiB", (g_total_mem - g_free_mem) / 1024 / 1024);
}

uint64_t phys_alloc(uint64_t addr, uint64_t size)
{
	klog("size %i, converting to %i blocks", size,
		 (size + BLOCK_SIZE - 1) / BLOCK_SIZE);
	uint64_t blocks = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;

	for (uint64_t i = addr; i < g_highest_addr; i += BLOCK_SIZE) {
		if (_phys_alloc_range(i, blocks) == NULL)
			continue;

		klog("allocated %i blocks at 0x%lx", blocks, i);
		return i;
	}

	// out of memory
	panic();
	return 0;
}

void phys_free(uint64_t addr, uint64_t size)
{
	uint64_t blocks = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;

	for (uint64_t i = addr; i < addr + (blocks * BLOCK_SIZE); i += BLOCK_SIZE) {
		if (!bitmap_test_range(i, 1)) {
			g_free_mem += BLOCK_SIZE;
		}

		bitmap_set(i);
	}

	klog("freed %i blocks from 0x%lx", blocks, addr);
}

uint64_t *_phys_alloc_range(uint64_t addr, uint64_t size)
{
	uint64_t blocks = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;

	if (!bitmap_test_range(addr, blocks)) {
		return NULL;
	}

	bitmap_set_range(addr, blocks);
	g_free_mem -= size;
	return (uint64_t *)addr;
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