#include <KadOS.h>

void k_main()
{
	disable();

	cls();
	printf("Initializing Descriptor Tables...\t");
	init_descriptor_tables();
	printf("\t[Done]\n");

	printf("Initializing Keyboard...\t\t\t");
	Keyboard();
	printf("\t[Done]\n");

	enable();

	puts("Welcome to KadOS!");
	for(;;)
	{
		while(!kbhit());
		putch(getch());
	}
}
