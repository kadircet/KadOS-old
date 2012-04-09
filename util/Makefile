CFLAGS = -O2 -Wall -I../include -nostdlib -nostdinc -fno-builtin -fno-stack-protector

all: string.o port.o

string.o: string.c
	djecho "[GCC ] string"
	gcc $(CFLAGS) -c string.c

port.o: port.c
	djecho "[GCC ] port"
	gcc $(CFLAGS) -c port.c

clean:
	del *.o
