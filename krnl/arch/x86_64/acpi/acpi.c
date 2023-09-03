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

#include <boot/boot.h>
#include <mem/phys.h>

#include <luxe.h>

void acpi_init()
{
	klog("rsdp is at 0x%8llx", rsdp_request.response->address);

	uint8_t rsdp_checksum = 0;
	uint8_t *rsdp_ptr = (uint8_t *)rsdp_request.response->address;
	for (uintptr_t i = 0; i < sizeof(rsdp_t); i++) {
		rsdp_checksum += rsdp_ptr[i];
	}
	assert((rsdp_checksum & 0xFF) == 0);

	rsdp_t *rsdp = (rsdp_t *)rsdp_request.response->address;
	if (rsdp->revision == 0) {
		rsdt_init(false);
	} else if (rsdp->revision >= 2) {
		uint8_t xsdp_checksum = 0;
		uint8_t *xsdp_ptr = (uint8_t *)rsdp_request.response->address;
		for (uintptr_t i = 0; i < sizeof(xsdp_t); i++) {
			xsdp_checksum += xsdp_ptr[i];
		}

		assert((xsdp_checksum & 0xFF) == 0);
		rsdt_init(true);
	}

	klog("done");
}

void *_find_sdt(bool use_xsdt, char *signature)
{
	if (use_xsdt) {
		int entries = (g_xsdt->header.length - sizeof(g_xsdt->header)) / 8;
		for (int i = 0; i < entries; i++) {
			sdt_t *header = (sdt_t *)(uintptr_t)PHYS_TO_VIRT(g_xsdt->sdt[i]);
			if (!strncmp(header->signature, signature, 4)) {
				klog("found header with signature %.4s", header->signature);
				return (void *)header;
			}
		}
	} else {
		int entries = (g_rsdt->header.length - sizeof(g_rsdt->header)) / 4;
		for (int i = 0; i < entries; i++) {
			sdt_t *header = (sdt_t *)(uintptr_t)PHYS_TO_VIRT(g_rsdt->sdt[i]);
			if (!strncmp(header->signature, signature, 4)) {
				klog("found header with signature %.4s", header->signature);
				return (void *)header;
			}
		}
	}

	return NULL;
}