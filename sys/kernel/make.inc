#
# Makefile for the ChikenOS kernel
#

INCLUDEPATH = libc/include

KERNEL_OBJ = $(KERNEL_PATH)/loader.o $(KERNEL_PATH)/kmain.o $(KERNEL_PATH)/console.o $(KERNEL_PATH)/gdt.o

kernel.bin: $(KERNEL_OBJ) libc.a
	ld -T $(KERNEL_PATH)/ld.conf -o $@ $+

$(KERNEL_PATH)/%.o: $(KERNEL_PATH)/%.c
	gcc -c -m32 -I$(INCLUDEPATH) -Wall -o $@ $<

$(KERNEL_PATH)/%.o: $(KERNEL_PATH)/%.s
	as -o $@ $<

kernel_clean:
	rm -f $(KERNEL_PATH)/*.o $(KERNEL_PATH)/kernel.bin

