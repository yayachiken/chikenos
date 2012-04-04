#include <string.h>

// code descriptor + data descriptor + null descriptor
#define DESCR_COUNT 3

extern void gdt_flush();

static unsigned long long int gdt[DESCR_COUNT];

struct GDT_properties
{
	int limit;
	int base;
	char access;
	unsigned char flags;
};

struct gdt_ptr
{
	unsigned short len;
	unsigned int base;
} __attribute__((packed));

struct gdt_ptr gdtp;

void gdt_make_entry(char *buf, struct GDT_properties prop)
{
	buf[0] = prop.limit & 0xFF;
	buf[1] = (prop.limit >> 8) & 0xFF;
	buf[2] = prop.base & 0xFF;
	buf[3] = (prop.base >> 8) & 0xFF;
	buf[4] = (prop.base >> 16) & 0xFF;
	buf[5] = prop.access;
	buf[6] = ((prop.limit >> 16) & 0x0F) | (prop.flags & 0xF0);
	buf[7] = (prop.base >> 24) & 0xFF;
}

void gdt_init()
{
	struct GDT_properties code, data;
	
	// Zero out GDT
	memset(&gdt[0], 0, DESCR_COUNT * 8);
	
	// Null descriptor
	gdt[0] = 0;
	
	// Ring 0 code descriptor
	code.limit = 0xFFFFFFFF;
	code.base = 0x00000000;
	code.access = 0x9A;	// 10011110b
	code.flags = 0xCF;	// 1100XXXXb
	gdt_make_entry((char*) &gdt[1], code);
	
	// Ring 0 data descriptor
	data.limit = 0xFFFFFFFF;
	data.base = 0x00000000;
	data.access = 0x92;	// 10010010b
	data.flags = 0xCF;	// 1100XXXXb
	gdt_make_entry((char*) &gdt[2], data);
	
	gdtp.len = DESCR_COUNT*8-1;
	gdtp.base = (unsigned int)&gdt;
	
	gdt_flush();
}
