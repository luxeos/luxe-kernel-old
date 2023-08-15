/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <acpi/acpi.h>
#include <acpi/madt.h>
#include <mem/phys.h>

#include <luxe.h>

static uint8_t g_num_isos = 0;
static uint8_t g_lapic_count = 0;
static uint8_t g_x2lapic_count = 0;

static uint64_t g_ioapic_ptr = 0;
static uint64_t g_lapic_ptr = 0;

static madt_lapic_t *g_lapic_ids[CONFIG_CPU_MAX] = { 0 };
static apic_x2lapic_t *g_x2lapic_ids[CONFIG_CPU_MAX] = { 0 };
static apic_iso_t *g_apic_isos[16] = { 0 };

void madt_parse(madt_t *madt)
{
	g_lapic_ptr = PHYS_TO_VIRT(madt->lapic_address);
	uint8_t *ptr = (uint8_t *)(madt + 1);
	uint8_t *end = (uint8_t *)madt + madt->header.length;

	while (ptr < end) {
		apic_hdr_t *hdr = (apic_hdr_t *)ptr;
		switch (hdr->type) {
		case 0: {
			g_lapic_ids[g_lapic_count] = (madt_lapic_t *)hdr;
			klog("found lapic entry, id %i", g_lapic_count);
			g_lapic_count++;
			break;
		}
		case 1: {
			g_ioapic_ptr =
				PHYS_TO_VIRT((uint64_t)((madt_ioapic_t *)hdr)->ioapic_addr);
			klog("found ioapic ptr @ 0x%llx", g_ioapic_ptr);
			break;
		}
		case 2: {
			g_apic_isos[g_num_isos] = (apic_iso_t *)hdr;
			klog("found ioapic iso, bus %i, irq %i, gsi %i",
				 g_apic_isos[g_num_isos]->bus, g_apic_isos[g_num_isos]->irq,
				 g_apic_isos[g_num_isos]->gsi);
			g_num_isos++;
			break;
		}
		case 3: {
			klog("found ioapic nmi");
			break;
		}
		case 4: {
			klog("found lapic nmi");
			break;
		}
		case 5: {
			g_lapic_ptr = PHYS_TO_VIRT(
				(uint64_t)((apic_lapic_override_t *)hdr)->lapic_addr);
			klog("found lapic ptr @ 0x%llx", g_lapic_ptr);
			break;
		}
		case 9: {
			g_x2lapic_ids[g_x2lapic_count] = (apic_x2lapic_t *)hdr;
			klog("found x2apic");
			break;
		}
		default: {
			klog("found invalid madt entry %i", hdr->type);
			break;
		}
		}

		ptr += hdr->length;
	}

	klog("done");
}

uint64_t get_ioapic_addr()
{
	return g_ioapic_ptr;
}

uint64_t get_lapic_addr()
{
	return g_lapic_ptr;
}

apic_iso_t *get_ioapic_iso(uint8_t irq)
{
	return g_apic_isos[irq];
}

uint64_t get_cpu_count()
{
	return g_lapic_count;
}

uint8_t get_cpu_id(uint64_t num)
{
	return g_lapic_ids[num]->apic_id;
}