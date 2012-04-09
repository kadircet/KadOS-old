#include <port.h>

inline void outportb(unsigned short port, unsigned char data)
{
    __asm__("outb %1, %0" : : "d"(port), "a" (data));
}

inline unsigned char inportb(unsigned short port)
{
	unsigned char data;
	__asm__("inb %1, %0" : "=a" (data) : "d" (port));
	return data;
}

inline void outportw(unsigned short port, unsigned short data)
{
    __asm__("outw %1, %0" : : "d"(port), "a" (data));
}

inline unsigned short inportw(unsigned short port)
{
	unsigned short data;
	__asm__("inw %1, %0" : "=a" (data) : "d" (port));
	return data;
}

inline void enable()
{
	asm volatile ("sti");
}

inline void disable()
{
	asm volatile("cli");
}

inline void halt()
{
	asm volatile("hlt");
}