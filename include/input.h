#ifndef KadOS_Input
#define KadOS_Input

#define ScrollLock (unsigned char)0x01
#define NumLock (unsigned char)0x02
#define CapsLock (unsigned char)0x04

#define KEY_UP      15
#define KEY_DOWN    40
#define KEY_LEFT    20
#define KEY_RIGHT   30

#define BUFFSIZE 256

void scanf(char *format, ...);
int kbhit();
unsigned char getch();
void Keyboard();

#endif