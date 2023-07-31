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

static uint64_t *bitmap = NULL;

void bitmap_set(uint8_t bit)
{
	bitmap[bit / 8] |= (1 << (bit % 8));
}

void bitmap_clear(uint8_t bit)
{
	bitmap[bit / 8] &= ~(1 << (bit % 8));
}

uint8_t bitmap_test(uint8_t bit)
{
	return bitmap[bit / 8] & (1 << (bit % 8));
}

void phys_init()
{
	struct limine_memmap_response *mmap = memmap_request.response;
	for (uint8_t i = 0; i < mmap->entry_count; i++) {
		struct limine_memmap_entry *entry = mmap->entries[i];
		klog("entry %i, base: 0x%lx, length: 0x%lx, type: %s", i, entry->base, entry->length, _phys_get_type(entry->type));
	}
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