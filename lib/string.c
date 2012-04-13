#include <string.h>

int strlen(char *s)
{
	int t=0;
	while(*s++)
		t++;
	return t;
}

void *memset(void *ptr, unsigned char value, unsigned int num)
{
	unsigned char *pos = (unsigned char *)ptr;
	while(num--) *pos++ = value;
	return ptr;
}

void *memsetw(void *ptr, unsigned short value, unsigned int num)
{
	unsigned short *pos = (unsigned short *)ptr;
	while(num--) *pos++ = value;
	return ptr;
}
