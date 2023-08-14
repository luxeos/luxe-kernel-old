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

typedef struct {
	uint8_t type;
	uint8_t length;
} __attribute__((packed)) apic_hdr_t;

typedef struct {
	apic_hdr_t header;
	uint8_t proc_id;
	uint8_t apic_id;
	uint32_t flags;
} __attribute__((packed)) madt_lapic_t;

typedef struct {
	apic_hdr_t header;
	uint8_t ioapic_id;
	uint8_t reserved;
	uint32_t ioapic_addr;
	uint32_t gsi_base;
} __attribute__((packed)) madt_ioapic_t;

typedef struct {
	apic_hdr_t header;
	uint8_t bus;
	uint8_t irq;
	uint32_t gsi;
	uint16_t flags;
} __attribute__((packed)) apic_iso_t;

typedef struct {
	apic_hdr_t header;
	uint8_t nmi;
	uint8_t reserved;
	uint16_t flags;
	uint32_t gsi;
} __attribute__((packed)) apic_ioapic_nmi_t;

typedef struct {
	apic_hdr_t header;
	uint8_t proc_id;
	uint16_t flags;
	uint8_t lint;
} __attribute__((packed)) apic_lapic_nmi_t;

typedef struct {
	apic_hdr_t header;
	uint64_t lapic_addr;
} __attribute__((packed)) apic_lapic_override_t;

typedef struct {
	apic_hdr_t header;
	uint16_t reserved;
	uint32_t proc_id;
	uint32_t flags;
	uint32_t acpi_id;
} __attribute__((packed)) apic_x2lapic_t;

void madt_parse(madt_t *madt);

uint64_t get_ioapic_addr();
uint64_t get_lapic_addr();
apic_iso_t *get_ioapic_iso(uint8_t irq);

#endif /* __MADT_H_ */