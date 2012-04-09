CFLAGS = -O2 -Wall -I../include -nostdlib -nostdinc -fno-builtin -fno-stack-protector

output.o: output.c
	djecho "[GCC ] output"
	gcc $(CFLAGS) -c output.c

clean:
	del *.o
