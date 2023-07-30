/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#ifndef __LAPIC_H_
#define __LAPIC_H_

#include <luxe.h>

#define IA32_APIC_BASE 0x1B

#define APIC_SPURIOUS_VECTOR 0xFF
#define APIC_ENABLE (1 << 8)
#define APIC_REG_VER 0x30
#define APIC_EOI 0xB0
#define LAPIC_ID 0x20

void lapic_init();

#endif /* __LAPIC_H_ */