#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

void gdt_init();
void idt_init();
void pic_init();

void int_disable();
void int_enable();

#endif

