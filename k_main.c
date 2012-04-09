#include <KadOS.h>

extern long code;
extern long data;
extern long bss;
extern long end;

void k_main()
{
	cls();
	puts("Welcome to KadOS!");
	printf("%p %p %p %p\n", &code, &data, &bss, &end);
	for(;;);
}
