#
# Makefile for the ChikenOS kernel
#

.PHONY: clean

INCLUDEPATH = ../../libc/include

OBJ = loader.o kmain.o console.o gdt.o

kernel.bin: $(OBJ)
	ld -T ld.conf -o $@ $(OBJ) ../../libc/libc.a

%.o: %.c
	gcc -c -m32 -I$(INCLUDEPATH) -Wall -o $@ $<

%.o: %.s
	as -o $@ $<

clean:
	rm -f *.o kernel.bin

