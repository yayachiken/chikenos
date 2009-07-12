// code descriptor + data descriptor + null descriptor
#define DESCR_COUNT 3

static unsigned long long int gdt[DESCR_COUNT];

struct GDT_properties
{
	int limit;
	int base;
	char access;
	char flags;
};

void gdt_make_entry(char *buf, struct GDT_properties prop)
{
	buf[0] = prop.limit & 0x000000FF;
	buf[1] = prop.limit & 0x0000FF00;
	buf[2] = prop.base & 0x000000FF;
	buf[3] = prop.base & 0x0000FF00;
	buf[4] = prop.base & 0x00FF0000;
	buf[5] = prop.access;
	buf[6] = (prop.flags & 0x0F) | (prop.limit & 0x000F0000);
	buf[7] = prop.base & 0xFF000000;
}

void gdt_init()
{
	struct GDT_properties code, data;
	
	// Null descriptor
	gdt[0] = 0;
	
	// Ring 0 code descriptor
	code.limit = 0xFFFFF;
	code.base = 0x00000000;
	code.access = 0x9E;	// 10011110b
	code.flags = 0xC;	// 1100b
	gdt_make_entry((char*) &gdt[1], code);
	
	// Ring 0 data descriptor
	data.limit = 0xFFFFF;
	data.base = 0x00000000;
	data.access = 0x92;	// 10010010b
	data.flags = 0xC;	// 1100
	gdt_make_entry((char*) &gdt[2], data);
	
	struct
	{
		unsigned short int len;
		unsigned long long int *ptr;
	} __attribute__((packed))
	gdtp = { .len = DESCR_COUNT * 8, .ptr = gdt, };
	
	asm volatile("lgdt %0" : : "m" (gdtp));
}
