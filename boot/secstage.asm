[BITS 32]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov esp, 0x7C00

	mov byte [0xB8000], 'A'

hang:
	jmp hang
