/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#ifndef __APIC_H_
#define __APIC_H_

#include <luxe.h>

void apic_init();

void apic_eoi();
uint8_t apic_get_irq(uint8_t irq);

#endif /* __APIC_H_ */