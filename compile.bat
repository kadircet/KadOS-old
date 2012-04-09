@echo off
cd boot
nasm -fbin -ostage1.o boot.asm
nasm -fbin -ostage2.o secstage.asm
cd ..

nasm -faout start.asm -ostart.o
gcc -ffreestanding -c k_main.c -o main.o
ld -T link.ld -o kernel.bin start.o main.o

copy /B boot\stage1.o + kernel.bin KadOS.img
pause
