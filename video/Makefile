CFLAGS = -O2 -Wall -I../include -nostdlib -nostdinc -fno-builtin -fno-stack-protector

all: output.o input.o

output.o: output.c
	echo [GCC ] output
	gcc $(CFLAGS) -c output.c

input.o: input.c
	echo [GCC ] input
	gcc $(CFLAGS) -c input.c

clean:
	del *.o
