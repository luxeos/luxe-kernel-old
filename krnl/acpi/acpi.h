/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#ifndef __ACPI_H_
#define __ACPI_H_

#include <boot/boot.h>

typedef struct {
	char signature[4];
	uint32_t length;
	uint8_t revision;
	uint8_t checksum;
	char oem_id[6];
	char oem_tableid[8];
	uint32_t oem_revision;
	uint32_t creator_id;
	uint32_t creator_revision;
	// the specific tables follow here
} __attribute__((packed)) sdt_t;

void acpi_init();

#endif /* __ACPI_H_ */