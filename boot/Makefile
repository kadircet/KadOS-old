all: boot

clean:
	del *.o

head.o: head.asm
	djecho.exe "[ASM ] head"
	nasm -faout head.asm -o head.o

boot.o: boot.asm
	djecho.exe "[ASM ] bootload"
	nasm -fbin boot.asm -o boot.o

boot: boot.o head.o
	djecho.exe "[DONE] bootloader"
