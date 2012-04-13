#include <KadOS.h>

int isAlpha(char c)
{
	if(c>='A' && c<='Z')
		return 1;
	if(c>='a' && c<='z')
		return 1;
	return 0;
}

int isNumeric(char c)
{
	if(c>='0' && c<='9')
		return 1;
	return 0;
}

int isAplhaNumeric(char c)
{
	return (isNumeric(c)||isAlpha(c));
}

int pow(int b, int p)
{
	int retv=1;
	while(p--)retv*=b;
	return retv;
}