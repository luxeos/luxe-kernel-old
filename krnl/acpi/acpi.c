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
#include <mem/phys.h>
#include <boot/boot.h>
#include <luxe.h>

void acpi_init()
{
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