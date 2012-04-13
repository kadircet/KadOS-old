#include <KadOS.h>

unsigned short *screen = (unsigned short *)0xB8000;
unsigned short attr = 0x0700;
int cursorx=0, cursory=0, ci=0;

void updatecursor()
{
	unsigned int index = (cursory * 80) + cursorx;
	outportb(VGA_CRTC_INDEX, 14);
	outportb(VGA_CRTC_DATA,  (index >> 8));
	outportb(VGA_CRTC_INDEX, 15);
	outportb(VGA_CRTC_DATA,  (index & 0xFF));
}

void showcursor()
{
	outportb(VGA_CRTC_INDEX, 10);
	outportb(VGA_CRTC_DATA, (inportb(VGA_CRTC_DATA) & ~0x20));
}

void hidecursor()
{
	outportb(VGA_CRTC_INDEX, 10);
	outportb(VGA_CRTC_DATA, (inportb(VGA_CRTC_DATA) | 0x20));
}

void cls()
{
	memsetw(screen, (attr | ' '), 80 * 25);
    cursorx = 0; cursory = 0;
    updatecursor();
}

void settextcolor(char fore, char back)
{
    attr = ((back << 12) | ((fore & 0x0F) << 8));
}

void gotoxy(int x, int y)
{
    cursorx = x; cursory = y;
    updatecursor();
}

unsigned char putch(unsigned char ch)
{
	if(ch==0)return 0;
	switch(ch)
	{
		case '\b':
			if(cursorx>0)
			{
				cursorx--;
				updatecursor();
				putch(' ');
				cursorx--;
			}
			break;
		case '\t':
			cursorx = (cursorx + 4) & ~(4 - 1);
			break;
		case '\r':
			cursorx=0;
			break;
		case '\n':
			cursorx=0;
			cursory++;
			break;
		default:
			if(ch>=' ')
			{
				 *(screen + (cursory * 80) + cursorx) = (attr | ch);
				 cursorx++;
			}
			break;
	}
	if(cursorx>=80)
	{
		cursorx=0;
		cursory++;
	}
	if(cursory>=25)
	{
		cursory=24;
		cursorx=0;
		int i=0;
		for(i=0;i<80*24;i++)
			*(screen+i) = *(screen+i+80);
		memsetw(screen+80*24,' ',80);
	}
	updatecursor();
	return ch;
}

void puts(char *text)
{
	while(*text)
		putch(*text++);
	putch('\n');
}

void putsnocr(char *text)
{
	while(*text)
		putch(*text++);
}

void putdec(int x)
{
	if(x==0)
	{
		putch('0');
		return;
	}
	int i=0;
	char number[20];
	if(x<0)
	{
		x=-x;
		putch('-');
	}
	while(x>0)
	{
		number[i++]=x%10+'0';
		x/=10;
	}
	for(i--;i>=0;i--)
		putch(number[i]);
}

void puthex(int x)
{
	if(x==0)
	{
		putch('0');
		return;
	}
	putsnocr("0x");
	int i=0;
	char number[17];
	while(x>0)
	{
		number[i++]=(x%16<10)?x%16+'0':x%16-10+'A';
		x/=16;
	}
	for(i--;i>=0;i--)
		putch(number[i]);
}

void printf(char *format, ...)
{
	va_list arg;
	va_start(arg,format);
	int n;
	char c;
	char *s;
	while(*format)
	{
		switch(*format)
		{
			case '%':
				format++;
				switch(*format)
				{
					case '%':
						putch(*format);
						break;
					case 'd':
						n = va_arg(arg,int);
						putdec(n);
						break;
					case 'x':
						n = va_arg(arg,int);
						puthex(n);
						break;
					case 'p':
						n = va_arg(arg,int);
						puthex(n);
						break;
					case 'c':
						c = (char)va_arg(arg,int);
						putch(c);
						break;
					case 's':
						s = va_arg(arg,char*);
						putsnocr(s);
						break;
				}
				break;
			default:
				putch(*format);
				break;
		}
		format++;
	}
	va_end(arg);
}
