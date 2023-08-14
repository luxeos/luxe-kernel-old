/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#ifndef __PIC_H_
#define __PIC_H_

#include <luxe.h>

#define PIC1_COMD 0x20
#define PIC1_DATA 0x21
#define PIC2_COMD 0xA0
#define PIC2_DATA 0xA1

#define PIC_REMAP_OFFSET 0x20

void pic_remap();
void pic_mask(uint8_t irq);
void pic_disable();

#endif /* __PIC_H_ */