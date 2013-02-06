/*
 * Ports stuff. Copied from planlOS by Mathias Gottschlag.
 * LICENSE: X11
 */

#ifndef PORTS_H_INCLUDED
#define PORTS_H_INCLUDED

static inline void io_wait()
{
	asm("outb %%al, $0x80"::"a"(0));
}

/**
 * Writes one byte to the port.
 */
static inline void outb(unsigned short port, unsigned char data)
{
	asm("outb %0, %1"::"a"(data), "Nd"(port));
}

/**
 * Reads one byte from the port.
 */
static inline char inb(unsigned short port)
{
	char data;
	asm("inb %1, %0":"=a"(data):"Nd"(port));
	return data;
}

/**
 * Writes one byte to the port and waits a bit.
 */
static inline void outb_wait(unsigned short port, unsigned char data)
{
	asm("outb %0, %1"::"a"(data), "Nd"(port));
	asm("outb %%al, $0x80"::"a"(0));
}

/**
 * Writes one word to the port.
 */
static inline void outw(unsigned short port, unsigned short data)
{
	asm("outw %0, %1"::"a"(data), "Nd"(port));
}

/**
 * Reads one word from the port.
 */
static inline short inw(unsigned short port)
{
	short data;
	asm("inw %1, %0":"=a"(data):"Nd"(port));
	return data;
}

/**
 * Writes one 32bit integer to the port.
 */
static inline void outl(unsigned short port, unsigned int data)
{
	asm("outl %0, %1"::"a"(data), "Nd"(port));
}

/**
 * Reads a 32bit integer from the port.
 */
static inline int inl(unsigned short port)
{
	int data;
	asm("inl %1, %0":"=a"(data):"Nd"(port));
	return data;
}

#endif
