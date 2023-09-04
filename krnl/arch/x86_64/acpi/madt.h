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

#include <luxe.h>

typedef struct {
	sdt_t header;
	uint32_t lapic_addr;
	uint32_t flags;
} __attribute__((packed)) madt_t;

typedef struct {
	uint8_t type;
	uint8_t length;
} __attribute__((packed)) apic_header_t;

typedef struct {
	apic_header_t header;
	uint8_t acpi_proc_id;
	uint8_t apic_id;
	uint32_t flags;
} __attribute__((packed)) apic_lapic_t;

typedef struct {
	apic_header_t header;
	uint8_t ioapic_id;
	uint8_t reserved;
	uint32_t ioapic_addr;
	uint32_t gsi_base;
} __attribute__((packed)) apic_ioapic_t;

typedef struct {
	apic_header_t header;
	uint8_t bus;
	uint8_t irq;
	uint32_t gsi;
	uint16_t flags;
} __attribute__((packed)) apic_iso_t;

extern madt_t *g_madt;

void madt_init(void);

#endif /* __MADT_H_ */