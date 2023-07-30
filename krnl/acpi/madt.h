/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#ifndef __MADT_H_
#define __MADT_H_

#include <acpi/acpi.h>

typedef struct {
	sdt_t header;
	uint32_t lapic_address;
	uint32_t flags;
} __attribute__((packed)) madt_t;

#endif /* __MADT_H_ */