[BITS 16]
[ORG 0x7C00]

	mov cx, boot
	call print

	call a20

	xor ax, ax
	mov es, ax
	mov bx, 0x1000
	call read_kernel

	cli
	xor ax, ax
	mov ds, ax

	lgdt [gdt_desc]
	lidt [idt_desc]

	mov eax, cr0
	or eax, 0x01
	mov cr0, eax

	jmp 0x08:0x1000


;Prints the string at [cx]
;string must be null terminated
print:
	push ax
	push bx

.putc:
	mov ah, 0x0E
	mov bx, cx
	mov al, [bx]
	mov bh, 0x0F
	mov bl, 0x00

	or al, al
	jz .return

	int 0x10
	inc cx
	jmp .putc

.return:
	pop bx
	pop ax
	ret
;END OF print


;makes floppy drive ready
;to read the kernel
reset_drive:
	push ax
	push cx

	mov cx, reset
	call print

.try:
	mov ah, 0x00
	int 0x13
	or ah, ah
	jnz .try

	mov cx, done
	call print
	pop cx
	pop ax
	ret
;END OF reset_drive


;reads the kernel from
;the floppy
read_kernel:
	push ax
	push cx

.try:
	call reset_drive
	mov cx, kernel
	call print

	mov ah, 0x02
	mov al, 0x12
	mov ch, 0x00
	mov cl, 0x02
	mov dh, 0x00
	int 0x13
	or ah, ah
	jnz .try
	
	mov cx, done
	call print

	pop cx
	pop ax
	ret
;END OF read_kernel

;enables A20 line
a20:
	push ax
	in al, 0x92
	or al, 0x02
	out 0x92, al
	pop ax
	ret
;END OF a20


;variables
boot:	db "Boot Started!", 0x0D, 0x0A, 0x00
reset:	db "Reseting Drive.. ", 0x00
kernel:	db "Reading Kernel.. ", 0x00
done:	db "[DONE]", 0x0D, 0x0A, 0x00
;END OF variables

;gdt
gdt:

gdt_null:
	dd 0x00
	dd 0x00

gdt_code:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 10011010b
	db 11001111b
	db 0x00

gdt_data:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 10010010b
	db 11001111b
	db 0x00

gdt_end:

gdt_desc:
	dw gdt_end - gdt -1
	dd gdt

idt_desc:
	dw 0x00
	dd 0x00


times 510-($-$$) db 0x00
dw 0xAA55
