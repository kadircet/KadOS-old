CFLAGS = -O2 -Wall -Iinclude -nostdlib -nostdinc -fno-builtin -fno-stack-protector

all: KadOS
	"C:\Program Files\Bochs-2.5.1\bochs.exe" -f floppy.bxrc -q -log KadOS.log

clean:
	del *.o
	make -s -C boot clean
	make -s -C util clean
	make -s -C video clean

bind.o: binder.c
	echo [GCC ] Binder
	gcc binder.c -obind.o

k_main.o: k_main.c
	make -s -C boot
	make -s -C video
	make -s -C util
	echo [GCC ] Main
	gcc $(CFLAGS) -c k_main.c

kernel.o: k_main.o
	djecho [LINK] kernel.bin
	ld -T link.ld -o kernel.o boot/head.o k_main.o util/string.o util/port.o video/output.o util/isr.o util/interrupt.o util/flush.o util/desc_tables.o video/input.o util/math.o

KadOS:	kernel.o bind.o
	bind KadOS.img boot\boot.o kernel.o
	echo [DONE] KadOS

cd: KadOS
	mkdir cd
	copy KadOS.img cd
	mkisofs -o KadOS.iso -A KadOS -b KadOS.img cd
	echo [DONE] CDROM
	"C:\Program Files\Bochs-2.5.1\bochs.exe" -f cd.bxrc -q -log KadOS.log

floppy: KadOS
	"C:\Program Files\Bochs-2.5.1\bochs.exe" -f floppy.bxrc -q -log KadOS.log
