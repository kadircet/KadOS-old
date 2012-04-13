[BITS 32]

global _start, _kernel_stack
extern _k_main
[EXTERN code]
[EXTERN bss]
[EXTERN end]

SECTION .text
_start:
	jmp short _startup
	align 4
	
_startup:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov  esp, _kernel_stack
	call _k_main
	
	cli
	hlt
        
SECTION .bss
	resb 8192
_kernel_stack:
