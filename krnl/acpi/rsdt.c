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
#include <acpi/rsdt.h>
#include <acpi/madt.h>
#include <luxe.h>

xsdt_t *g_xsdt;
rsdt_t *g_rsdt;

madt_t *g_madt;

void rsdt_init(bool use_xsdt)
{
	if (use_xsdt) {
		xsdp_t *rsdp = rsdp_request.response->address;
		uint8_t xsdt_checksum = 0;
		uint8_t *xsdt_ptr = (uint8_t *)rsdp;
		for (uintptr_t i = 0; i < sizeof(xsdt_t); i++) {
			xsdt_checksum += xsdt_ptr[i];
		}

		assert((xsdt_checksum & 0xFF) == 0);
		g_xsdt = (xsdt_t *)(uintptr_t)rsdp->xsdt_addr;
	} else {
		rsdp_t *rsdp = rsdp_request.response->address;
		uint8_t rsdt_checksum = 0;
		uint8_t *rsdt_ptr = (uint8_t *)rsdp;
		for (uintptr_t i = 0; i < sizeof(rsdt_t); i++) {
			rsdt_checksum += rsdt_ptr[i];
		}

		assert((rsdt_checksum & 0xFF) == 0);
		g_rsdt = (rsdt_t *)(uintptr_t)rsdp->rsdt_addr;
	}

	// we'll find all sdt's here
	g_madt = (madt_t *)_rsdt_find_sdt(use_xsdt, "APIC");
	if (g_madt == NULL) {
		panic();
	}
}

void *_rsdt_find_sdt(bool use_xsdt, char *signature)
{
	if (use_xsdt) {
		int entries = (g_xsdt->header.length - sizeof(g_xsdt->header)) / 8;
		for (int i = 0; i < entries; i++) {
			sdt_t *header = (sdt_t *)(uintptr_t)g_xsdt->sdt[i];
			if (!strncmp(header->signature, signature, 4)) {
				klog("found header with signature %.4s", header->signature);
				return (void *)header;
			}
		}
	} else {
		int entries = (g_rsdt->header.length - sizeof(g_rsdt->header)) / 4;
		for (int i = 0; i < entries; i++) {
			sdt_t *header = (sdt_t *)(uintptr_t)g_rsdt->sdt[i];
			if (!strncmp(header->signature, signature, 4)) {
				klog("found header with signature %.4s", header->signature);
				return (void *)header;
			}
		}
	}

	return NULL;
}