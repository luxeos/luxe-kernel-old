/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#ifndef __RSDT_H_
#define __RSDT_H_

#include <acpi/acpi.h>
#include <acpi/madt.h>
#include <luxe.h>

typedef struct {
	char signature[8]; // "RSDT PTR "
	uint8_t checksum;
	char oem_id[6];
	uint8_t revision;
	uint32_t rsdt_addr;
} __attribute__((packed)) rsdp_t;

typedef struct {
	rsdp_t rsdp;
	uint32_t length;
	uint64_t xsdt_addr;
	uint8_t checksum;
	uint8_t reserved[3];
} __attribute__((packed)) xsdp_t;

typedef struct {
	sdt_t header;
	uint32_t sdt[];
} __attribute__((packed)) rsdt_t;

typedef struct {
	sdt_t header;
	uint64_t sdt[];
} __attribute__((packed)) xsdt_t;

void rsdt_init(bool use_xsdt);

void *_rsdt_find_sdt(bool use_xsdt, char *signature);

#endif /* __RSDT_H_ */