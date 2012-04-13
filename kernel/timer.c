#include <KadOS.h>

static void timer_handler(registers regs)
{
	disable();
	
	static unsigned char lastsec = -1;
	unsigned char cursec, cause;

	outportb(0x70, 0x0C);
	cause = inportb(0x71);
	
	outportb(0x70, 0x02);
	cursec = inportb(0x71);
	
	//if (lastsec != cursec)
		//printf("%d\n", cursec);
	lastsec = cursec;

	outportb(0x20, 0x20);
	enable();
}

void timer()
{
	outportb(0x70, 0x02);
	outportb(0x71, 0x00);
	register_interrupt_handler(IRQ0, &timer_handler);
}
