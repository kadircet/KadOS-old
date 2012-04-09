
void k_main()
{
	unsigned char* const videomem = (unsigned char* const)0x0B8000;
	int i;
	for (i=0; i<80*25; i++)
	{
		*(videomem + 2*i) = ' ';
		*(videomem + 2*i+1) = 0x07;
	}
	for (i=0; i<10; i++)
	{
		*(videomem + 2*i) = 'A' + i;
	}
	for(;;);
}
