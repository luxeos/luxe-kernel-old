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

void lapic_init();

uint32_t lapic_in(uint16_t reg);
void lapic_out(uint16_t reg, uint32_t value);

#endif /* __LAPIC_H_ */