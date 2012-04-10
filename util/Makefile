CFLAGS = -O2 -Wall -I../include -nostdlib -nostdinc -fno-builtin -fno-stack-protector

all: string.o port.o isr.o flush.o interrupt.o desc_tables.o math.o

string.o: string.c
	echo [GCC ] string
	gcc $(CFLAGS) -c string.c

port.o: port.c
	echo [GCC ] port
	gcc $(CFLAGS) -c port.c

isr.o: isr.c
	echo [GCC ] isr
	gcc $(CFLAGS) -c isr.c

desc_tables.o: desc_tables.c
	echo [GCC ] desc_tables
	gcc $(CFLAGS) -c desc_tables.c

math.o: math.c
	echo [GCC ] math
	gcc $(CFLAGS) -c math.c

flush.o: flush.asm
	echo [NASM] flush
	nasm -faout -oflush.o flush.asm

interrupt.o: interrupt.asm
	echo [NASM] interrupt
	nasm -faout -ointerrupt.o interrupt.asm

clean:
	del *.o
