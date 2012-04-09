@echo off
nasm -fbin -ostage1 boot.asm
nasm -fbin -ostage2 secstage.asm
copy /B stage1 + stage2 boot
pause
