#CFLAGS = -O2 -Wall -Iinclude -nostdlib -nostdinc -fno-builtin -fno-stack-protector

OBJS = boot/head.o init/k_main.o kernel/port.o console/output.o \
	kernel/isr.o kernel/interrupt.o kernel/flush.o kernel/desc_tables.o \
	console/input.o kernel/timer.o

CFLAGS	=-Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -Iinclude
LDFLAG	=-s -x -M --oformat binary
LIBS	=lib/lib.a

AS	=nasm -faout
AS86	=nasm -fbin
LD	=ld
CC	=gcc
CPP	=gcc -E -nostdinc -Iinclude

all: KadOS
	"C:\Program Files\Bochs-2.5.1\bochs.exe" -f bin/floppy.bxrc -q -log KadOS.log

clean:
	find . -name '*.o' -print0 | xargs -0 rm -f
	rm -f bin/system
	rm -f bin/KadOS.log

	make -s clean -C lib

.s.o:
	echo [NASM] $*
	$(AS) -o $*.o $<
.c.o:
	echo [GCC ] $*
	$(CC) $(CFLAGS)	-c -o $*.o $<

bin/system: $(OBJS) $(LIBS)
	echo [LINK] bin/system
	$(LD) $(LDFLAG) -e _start -o bin/system $(OBJS) $(LIBS) > ld.out
	rm -f ld.out

boot/boot.o: boot/boot.s
	echo [NASM] boot
	$(AS86) -o boot/boot.o boot/boot.s

tools/bind: tools/bind.c
	echo [GCC ] $*
	$(CC) -o tools/bind tools/bind.c

lib/lib.a:
	make -s -C lib

KadOS:	boot/boot.o tools/bind bin/system
	tools/bind bin/KadOS.img boot/boot.o bin/system
	echo [DONE] KadOS

cd: KadOS
	cd bin
	rm cd -rf
	mkdir cd
	cp KadOS.img cd
	../tools/mkisofs -quiet -o KadOS.iso -A KadOS -b KadOS.img cd
	echo [DONE] CDROM
	"C:\Program Files\Bochs-2.5.1\bochs.exe" -f cd.bxrc -q > KadOS.log

floppy: KadOS
	cd bin
	"C:\Program Files\Bochs-2.5.1\bochs.exe" -f floppy.bxrc -q > KadOS.log
