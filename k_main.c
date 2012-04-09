#define blink 0x80
void k_main()
{
	unsigned char* const videomem = (unsigned char* const)0x0B8000;
	unsigned char const hello[] = "Welcome to KadOS!";
	int i;
	for (i=0; i<80*25; i++)
	{
		*(videomem + 2*i) = ' ';
		*(videomem + 2*i+1) = 0x02 | blink;
	}
	for (i=0; i<sizeof(hello); i++)
	{
		*(videomem + 2*i) = hello[i];
	}
	for(;;);
}
