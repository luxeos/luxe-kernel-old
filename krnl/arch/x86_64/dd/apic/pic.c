/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <dd/apic/pic.h>

#include <luxe.h>

void pic_remap()
{
	outb(PIC1_COMD, 0x11);
	outb(PIC2_COMD, 0x11);
	outb(PIC1_DATA, 0x20); // offset
	outb(PIC1_DATA, 0x28); // offset
	outb(PIC1_DATA, 0x04);
	outb(PIC2_DATA, 0x02);
	outb(PIC1_DATA, 0x01);
	outb(PIC2_DATA, 0x01);
	klog("remapped pic at offset 0x20");
}

void pic_disable()
{
	outb(PIC1_DATA, 0xFF);
	outb(PIC2_DATA, 0xFF);
	klog("disabled pic");
}