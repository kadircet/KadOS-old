[GLOBAL _gdt_flush]

_gdt_flush:
    mov eax, [esp+4]
    lgdt [eax]   

    mov ax, 0x10  
    mov ds, ax    
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush 
.flush:
    ret

[GLOBAL _idt_flush]

_idt_flush:
    mov eax, [esp+4] 
    lidt [eax] 
    ret
