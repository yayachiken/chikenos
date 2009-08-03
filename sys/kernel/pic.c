/*
 * A file for programming the PIC.
 */

#include <ports.h>

#define MASTER_CMD_PORT 0x20
#define SLAVE_CMD_PORT 0xA0
#define MASTER_DATA_PORT 0x21
#define SLAVE_DATA_PORT 0xA1

void pic_init()
{
	outb(MASTER_CMD_PORT,  0x11);
	io_wait();
	outb(SLAVE_CMD_PORT, 0x11);
	io_wait();
	outb(MASTER_DATA_PORT, 0xF0); // Map IRQ 0..7 to int 0xF0..0xF7
	io_wait();
	outb(SLAVE_DATA_PORT, 0xF8); // Map IRQ 8..15 to int 0xF8..0xFF
	io_wait();
	outb(MASTER_DATA_PORT, 0x04);
	io_wait();
	outb(SLAVE_DATA_PORT, 0x02);
	io_wait();
	outb(MASTER_DATA_PORT, 0x01);
	io_wait();
	outb(SLAVE_DATA_PORT, 0x01);
	io_wait();
	
	
	// Unmask interrupts
	outb(MASTER_CMD_PORT, 0x0);
	outb(SLAVE_CMD_PORT, 0x0);
}

void pic_eoi()
{
	outb(MASTER_CMD_PORT, 0x20);
}