#include <KadOS.h>

extern void gdt_flush(unsigned int);
extern void idt_flush(unsigned int);

static void init_gdt();
static void init_idt();
static void gdt_set_gate(int,unsigned int,unsigned int,unsigned char,unsigned char);
static void idt_set_gate(unsigned char,unsigned int,unsigned short,unsigned char);

gdt_entry gdt_entries[5];
gdt_ptr_t gdt_ptr;
idt_entry idt_entries[256];
idt_ptr_t idt_ptr;

extern isr_t interrupt_handlers[];

void init_descriptor_tables()
{
    init_gdt();
    init_idt();
    memset(&interrupt_handlers, 0, sizeof(isr_t)*256);
}

static void init_gdt()
{
    gdt_ptr.limit = (sizeof(gdt_entry) * 5) - 1;
    gdt_ptr.base  = (unsigned int)&gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);              
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); 
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); 
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); 
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); 

    gdt_flush((unsigned int)&gdt_ptr);
}

static void gdt_set_gate(int num, unsigned int base, unsigned int limit, unsigned char access, unsigned char gran)
{
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;
    
    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}

static void init_idt()
{
    idt_ptr.limit = sizeof(idt_entry) * 256 -1;
    idt_ptr.base  = (unsigned int)&idt_entries;

    memset(&idt_entries, 0, sizeof(idt_entry)*256);

    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);

    idt_set_gate( 0, (unsigned int)isr0 , 0x08, 0x8E);
    idt_set_gate( 1, (unsigned int)isr1 , 0x08, 0x8E);
    idt_set_gate( 2, (unsigned int)isr2 , 0x08, 0x8E);
    idt_set_gate( 3, (unsigned int)isr3 , 0x08, 0x8E);
    idt_set_gate( 4, (unsigned int)isr4 , 0x08, 0x8E);
    idt_set_gate( 5, (unsigned int)isr5 , 0x08, 0x8E);
    idt_set_gate( 6, (unsigned int)isr6 , 0x08, 0x8E);
    idt_set_gate( 7, (unsigned int)isr7 , 0x08, 0x8E);
    idt_set_gate( 8, (unsigned int)isr8 , 0x08, 0x8E);
    idt_set_gate( 9, (unsigned int)isr9 , 0x08, 0x8E);
    idt_set_gate(10, (unsigned int)isr10, 0x08, 0x8E);
    idt_set_gate(11, (unsigned int)isr11, 0x08, 0x8E);
    idt_set_gate(12, (unsigned int)isr12, 0x08, 0x8E);
    idt_set_gate(13, (unsigned int)isr13, 0x08, 0x8E);
    idt_set_gate(14, (unsigned int)isr14, 0x08, 0x8E);
    idt_set_gate(15, (unsigned int)isr15, 0x08, 0x8E);
    idt_set_gate(16, (unsigned int)isr16, 0x08, 0x8E);
    idt_set_gate(17, (unsigned int)isr17, 0x08, 0x8E);
    idt_set_gate(18, (unsigned int)isr18, 0x08, 0x8E);
    idt_set_gate(19, (unsigned int)isr19, 0x08, 0x8E);
    idt_set_gate(20, (unsigned int)isr20, 0x08, 0x8E);
    idt_set_gate(21, (unsigned int)isr21, 0x08, 0x8E);
    idt_set_gate(22, (unsigned int)isr22, 0x08, 0x8E);
    idt_set_gate(23, (unsigned int)isr23, 0x08, 0x8E);
    idt_set_gate(24, (unsigned int)isr24, 0x08, 0x8E);
    idt_set_gate(25, (unsigned int)isr25, 0x08, 0x8E);
    idt_set_gate(26, (unsigned int)isr26, 0x08, 0x8E);
    idt_set_gate(27, (unsigned int)isr27, 0x08, 0x8E);
    idt_set_gate(28, (unsigned int)isr28, 0x08, 0x8E);
    idt_set_gate(29, (unsigned int)isr29, 0x08, 0x8E);
    idt_set_gate(30, (unsigned int)isr30, 0x08, 0x8E);
    idt_set_gate(31, (unsigned int)isr31, 0x08, 0x8E);
    idt_set_gate(32, (unsigned int)irq0, 0x08, 0x8E);
    idt_set_gate(33, (unsigned int)irq1, 0x08, 0x8E);
    idt_set_gate(34, (unsigned int)irq2, 0x08, 0x8E);
    idt_set_gate(35, (unsigned int)irq3, 0x08, 0x8E);
    idt_set_gate(36, (unsigned int)irq4, 0x08, 0x8E);
    idt_set_gate(37, (unsigned int)irq5, 0x08, 0x8E);
    idt_set_gate(38, (unsigned int)irq6, 0x08, 0x8E);
    idt_set_gate(39, (unsigned int)irq7, 0x08, 0x8E);
    idt_set_gate(40, (unsigned int)irq8, 0x08, 0x8E);
    idt_set_gate(41, (unsigned int)irq9, 0x08, 0x8E);
    idt_set_gate(42, (unsigned int)irq10, 0x08, 0x8E);
    idt_set_gate(43, (unsigned int)irq11, 0x08, 0x8E);
    idt_set_gate(44, (unsigned int)irq12, 0x08, 0x8E);
    idt_set_gate(45, (unsigned int)irq13, 0x08, 0x8E);
    idt_set_gate(46, (unsigned int)irq14, 0x08, 0x8E);
    idt_set_gate(47, (unsigned int)irq15, 0x08, 0x8E);

    idt_flush((unsigned int)&idt_ptr);
}

static void idt_set_gate(unsigned char num, unsigned int base, unsigned short sel, unsigned char flags)
{
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

    idt_entries[num].sel     = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags   = flags;
}
