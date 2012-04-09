#ifndef KadOS_Output
#define KadOS_Output

#define VGA_CRTC_INDEX  0x3D4
#define VGA_CRTC_DATA   0x3D5

#define COLOR_BLACK     0
#define COLOR_BLUE      1
#define COLOR_GREEN     2
#define COLOR_AQUA      3
#define COLOR_RED       4
#define COLOR_PURPLE    5
#define COLOR_YELLOW    6
#define COLOR_WHITE     7
#define COLOR_GRAY      8
#define COLOR_LTBLUE    9
#define COLOR_LTGREEN   10
#define COLOR_LTAQUA    11
#define COLOR_LTRED     12
#define COLOR_LTPURPLE  13
#define COLOR_LTYELLOW  14
#define COLOR_LTWHITE   15

#define va_start(v,l) __builtin_va_start(v,l)
#define va_arg(v,l)   __builtin_va_arg(v,l)
#define va_end(v)     __builtin_va_end(v)
#define va_copy(d,s)  __builtin_va_copy(d,s)
typedef __builtin_va_list va_list;

void cls();
unsigned char putch(unsigned char ch);
void putsnocr(char *text);
void puts(char *text);
void settextcolor(char foreground, char background);
void gotoxy(int x, int y);
void putdec(int x);
void puthex(int x);
void printf(char *format, ...);
void hidecursor();
void showcursor();

#endif
