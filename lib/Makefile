#
# Makefile for some libs needed in the kernel.
#
# Note! Dependencies are done automagically by 'make dep', which also
# removes any old dependencies. DON'T put your own dependencies here
# unless it's something special (ie not a .c file).
#

AR	=ar
CC	=gcc
CFLAGS	=-Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -I../include

.c.o:
	echo [GCC ] $*
	$(CC) $(CFLAGS) \
	-c -o $*.o $<

OBJS  = math.o string.o

lib.a: $(OBJS)
	echo [ AR ] lib
	$(AR) rcs lib.a $(OBJS)

clean:
	find . -name '*.o' -print0 | xargs -0 rm -f
	rm -f lib.a
