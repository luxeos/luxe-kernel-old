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

void pic_mask(int irq)
{
	uint8_t port;

	if (irq < 8) {
		port = PIC1_DATA;
	} else {
		irq -= 8;
		port = PIC2_DATA;
	}

	uint8_t mask = inb(port);
	outb(port, mask | (1 << irq));
}

void pic_eoi(uint8_t irq)
{
	if (irq >= 8) {
		outb(PIC2_COMD, PIC_EOI);
	}
	outb(PIC1_COMD, PIC_EOI);
}