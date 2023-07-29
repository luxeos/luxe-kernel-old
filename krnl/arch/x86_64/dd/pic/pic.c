#include <dd/pic/pic.h>

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
}

void pic_disable()
{
}