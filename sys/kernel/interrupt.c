/*
 * This file defines functions for interrupt handling
 */

#include <string.h>

#define IDT_COUNT 255

void int_disable()
{
	asm volatile("cli");
}

void int_enable()
{
	asm volatile("sti");
}

struct idt_entry
{
	unsigned short offset_lo;
	unsigned short selector;
	unsigned char null_byte;
	unsigned char flags;
	unsigned short offset_hi;
} __attribute__ ((packed));

static struct idt_entry idt[IDT_COUNT];

void idt_set_descriptor(unsigned char int_no, unsigned int offset, unsigned char flags)
{
	idt[int_no].offset_lo = offset & 0x0000FFFF;
	idt[int_no].offset_hi = offset >> 16;
	idt[int_no].selector = 0x8;
	idt[int_no].flags = flags;
	idt[int_no].null_byte = 0; // just to make sure
}

extern void int_handle();
extern void int_ecode_handle();
extern void test_int();

void idt_init()
{
	// Zero out the IDT
	memset(&idt[0], 0, sizeof(struct idt_entry)*IDT_COUNT);
	
	int i;
	for(i=0; i < IDT_COUNT; i++)
	{
		if(i == 8 || i == 17 || (i >= 10 && i <= 14))
			idt_set_descriptor(i, (unsigned int) int_ecode_handle, 0x8E);
		else
			idt_set_descriptor(i, (unsigned int) int_handle, 0x8E);
	}
	
	idt_set_descriptor(0xF0, (unsigned int) test_int, 0x8E);
		
	struct idt_ptr
	{
		unsigned short len;
		struct idt_entry *ptr;
	} __attribute__ ((packed))
	idtp = { .len = (sizeof (struct idt_entry) * 256) - 1, .ptr = &idt[0],};
	
	asm volatile("lidt %0" : : "m" (idtp));
}
