CFLAGS = -O2 -Wall  -I. -nostdlib -nostdinc -fno-builtin -fno-stack-protector

all: KadOS
	"C:\Program Files\Bochs-2.5.1\bochs.exe" -f floppy.bxrc -q -log KadOS.log

clean:
	del *.o
	make -s -C boot clean	

bind.o: binder.c
	echo [GCC ] Binder
	gcc binder.c -obind.o

k_main.o: k_main.c
	make -s -C boot
	echo [GCC ] Main
	gcc $(CFLAGS) -c k_main.c

kernel.o: k_main.o
	djecho [LINK] kernel.bin
	ld -T link.ld -o kernel.o boot\head.o k_main.o

KadOS:	kernel.o bind.o
	bind KadOS.img boot\boot.o kernel.o
	echo [DONE] KadOS
