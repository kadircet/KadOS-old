#include <KadOS.h>

static int last=0;
char *newline = (char*)0x10FF88;
char *lastch = (char*)0x10FF89;
static char stdin[256]={0};
unsigned char leds;
char num,caps,ctrl,shift,alt;

char normal[] =
{
	0x00,0x1B,'1','2','3','4','5','6','7','8','9','0','*','-','\b',
	'\t','q','w','e','r','t','y','u','ý','o','p','g',129,'\n',
	0x80,'a','s','d','f','g','h','j','k','l','s','i',',',
	0x80,'<','z','x','c','v','b','n','m',148,135,'.',0x80,
	'*',0x80,' ',0x80,0x80,0x80,75,80,77,72,0x80,0x80,
	0x80,0x80,0x80,0x80,'7','8','9',0x80,'4','5','6',0x80,
	'1','2','3','0',177
};

char shifted[] =
{
	0,033,'!','\'','^','+','%','&','/','(',')','=','?','_','\b','\t',
	'Q','W','E','R','T','Y','U','I','O','P','Ð',154,'\n',0x80,
	'A','S','D','F','G','H','J','K','L','Þ','Ý',';',0x80,
	'>','Z','X','C','V','B','N','M',153,128,':',0x80,
	'*',0x80,' ',0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0x80,0x80,0x80,0x80,'7','8','9',0x80,'4','5','6',0x80,
	'1','2','3','0',177
};

char capsNormal[] =
{
	0x00,0x1B,'1','2','3','4','5','6','7','8','9','0','-','=','\b','\t',
	'Q','W','E','R','T','Y','U','I','O','P','[',154,'\n',0x80,
	'A','S','D','F','G','H','J','K','L','Þ',047,0140,0x80,
	'|','Z','X','C','V','B','N','M',153,128,':',0x80,
	'*',0x80,' ',0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0x80,0x80,0x80,0x80,'7','8','9',0x80,'4','5','6',0x80,
	'1','2','3','0',177
};

char capsShifted[] =
{
	0,033,'!','\'','^','+','%','&','/','(',')','=','?','_','\b','\t',
	'q','w','e','r','t','y','u','ý','o','p','{',128,'\n',0x80,
	'a','s','d','f','g','h','j','k','l','þ','i',';',0x80,
	0134,'z','x','c','v','b','n','m',148,135,':',0x80,
	'*',0x80,' ',0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0x80,0x80,0x80,0x80,'7','8','9',0x80,'4','5','6',0x80,
	'1','2','3','0',177
};

void WaitForReady(void)
{
 	while (inportb(0x64) & 0x02);
}

void SendCommand(unsigned char c)
{
 	WaitForReady();
 	outportb(0x64,c);
	WaitForReady();
}

void SendData(unsigned char data)
{
	WaitForReady();
	outportb(0x60, data);
	WaitForReady();
}

void SetRate(unsigned char rate)
{
	SendData(0xF3);
	SendData(rate);
}

void UpdateLeds(unsigned char led)
{
	if(led == 0)
	{
		leds = 0;
	}
	else
	{
		if (leds == (leds|led))
		{
			leds = leds^led;
		}
		else
		{
			leds = leds | led;
		}
	}
	SendData(0xED);
	SendData(leds);
}

int kb_special(unsigned char key)
{
	static int specKeyUp = 1;
	switch(key) 
	{
		case 0x36: //R-Shift down
		case 0x2A: //L-Shift down
			shift = 1;
			break;
		case 0xB6: //R-Shift up
		case 0xAA: //L-Shift up
			shift = 0;
			break;
		case 0x1D: //Control down
			ctrl = 1;
			break;
		case 0x9D: //Control up
			ctrl = 0;
			break;
		case 0x38: //Alt down
			alt = 1;
			break;
		case 0xB8: //Alt up
			alt = 0;
			break;
		case 0x3A: //Caps down
			if(specKeyUp == 1) 
			{
				caps = !caps;
				UpdateLeds(CapsLock);
				specKeyUp = 0;
			}
			break;
		case 0x45: //Num down
			if(specKeyUp == 1)
			{
				num = !num;
				UpdateLeds(NumLock);
				specKeyUp = 0;
			}
			break;
		case 0x46: //Scroll down
			if(specKeyUp == 1)
			{
				num = !num;
				UpdateLeds(ScrollLock);
				specKeyUp = 0;
			}
			break;
		case 0xBA: //Caps Up
		case 0xBB: //F1 Up
		case 0xBC: //F2 Up
		case 0xBD: //F3 Up
		case 0xBE: //F4 Up
		case 0xBF: //F5 Up
		case 0xC0: //F6 Up
		case 0xC1: //F7 Up
		case 0xC2: //F8 Up
		case 0xC3: //F9 Up
		case 0xC4: //F10 Up
		case 0xC5: //Num Up
		case 0xC6: //Scroll Up
			specKeyUp = 1;
			break;
		case 0xE0:
			break;
		default:
			return(0);
	}
	return (1);
}

int kbhit()
{
	if (last>0)
	{
		last--;
		return 1;
	}
	return 0;
}

void scanf(char *format, ...)
{
	hidecursor();
	va_list arg;
	va_start(arg,format);

	while(*newline==0)
	{
		putch('\r');
		putsnocr(stdin);
	}

	char number[30];
	char *stdin2=stdin;
	int *n;
	char *c;
	int i=0;
	int dgt=0;

	while(*format)
	{
		memset(number,0,30);
		switch(*format)
		{
			case '%':
				format++;
				switch(*format)
				{
					case 'd':
						i=0;
						while(!isNumeric(*stdin2))stdin2++;
						while(isNumeric(*stdin2))
						{
							number[i++]=*stdin2 - '0';
							stdin2++;
						}
						n = va_arg(arg,int*);
						dgt=--i;
						while(i+1)
							*n = *n + number[i]*pow(10,dgt-i),i--;
						break;
					case 'x':
						break;
					case 's':
						c = va_arg(arg,char*);
						while(isAplhaNumeric(*stdin2))
							*c++ = *stdin2++;
						break;
					case 'c':
						c = va_arg(arg,char*);
						*c = *stdin2;
						stdin2++;
						break;
				}
				break;
		}
		format++;
	}
	memset(stdin,0,256);
	last=0;
	*newline=0;

	va_end(arg);

	showcursor();
}

unsigned char getch()
{
	return *lastch;
}

static void keyb_handler(registers regs)
{
	disable();

	unsigned char scanCode = inportb(0x60), asciiCode=0;

	if(!(kb_special(scanCode) | (scanCode >= 0x80)))
	{
		if(shift)
		{
			if(!caps)
				asciiCode = shifted[scanCode];
			else
				asciiCode = capsShifted[scanCode];
		}
		else
		{
			if(!caps)
				asciiCode = normal[scanCode];
			else
				asciiCode = capsNormal[scanCode];
		}
		/*if(asciiCode=='\b')
		{
			last--;
			asciiCode=0;
		}*/
		if(last==BUFFSIZE-1)
			printf("Error stdin FULL overwriting..!");
		stdin[last++%256]=asciiCode;
		*lastch=asciiCode;
		*newline = *lastch=='\n';
	}

	outportb(0x20,0x20);
	enable();
}

void Keyboard()
{
	*lastch=0;
	*newline=0;
	caps = shift = 0;
	SendData(0xFF);		
	SendData(0xF4);		
	SetRate(0x00);	
	UpdateLeds(0);
	register_interrupt_handler(IRQ1, &keyb_handler);
}
