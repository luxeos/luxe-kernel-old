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

#include <luxe.h>

xsdt_t *g_xsdt;
rsdt_t *g_rsdt;

void rsdt_init(bool use_xsdt)
{
	if (use_xsdt) {
		xsdp_t *rsdp = (xsdp_t *)rsdp_request.response->address;
		uint8_t xsdt_checksum = 0;
		uint8_t *xsdt_ptr = (uint8_t *)rsdp;
		for (uintptr_t i = 0; i < sizeof(xsdt_t); i++) {
			xsdt_checksum += xsdt_ptr[i];
		}

		assert((xsdt_checksum & 0xFF) == 0);
		g_xsdt = (xsdt_t *)(uintptr_t)PHYS_TO_VIRT(rsdp->xsdt_addr);
	} else {
		rsdp_t *rsdp = (rsdp_t *)rsdp_request.response->address;
		uint8_t rsdt_checksum = 0;
		uint8_t *rsdt_ptr = (uint8_t *)rsdp;
		for (uintptr_t i = 0; i < sizeof(rsdt_t); i++) {
			rsdt_checksum += rsdt_ptr[i];
		}

		assert((rsdt_checksum & 0xFF) == 0);
		g_rsdt = (rsdt_t *)(uintptr_t)PHYS_TO_VIRT(rsdp->rsdt_addr);
	}

	// we'll find all sdt's here
	//
	// the general idea of parsing is like this:
	//	- find table
	//	- if the table is not found, panic
	//	- fill the appropriate structure
	//	- call the table's init function
	//
	// table = (table_t *)_find_sdt(use_xsdt, "SIG_");
	// assert(table != NULL);
	// table_init(table);

	klog("done");
}