#
# Makefile for the ChikenOS kernel
#

LIBC_INCLUDE_PATH = libc/include
SYS_INCLUDE_PATH = sys/include

KERNEL_OBJ = 	$(KERNEL_PATH)/loader.o \
		$(KERNEL_PATH)/kmain.o \
		$(KERNEL_PATH)/console.o \
		$(KERNEL_PATH)/gdt.o \
		$(KERNEL_PATH)/interrupt.o \
		$(KERNEL_PATH)/pic.o \
		$(KERNEL_PATH)/cpuid.o

kernel.bin: $(KERNEL_OBJ) libc.a
	ld -T $(KERNEL_PATH)/ld.conf -o $@ $+

$(KERNEL_PATH)/%.o: $(KERNEL_PATH)/%.c
	gcc -c -m32 -I$(LIBC_INCLUDE_PATH) -I$(SYS_INCLUDE_PATH)  -Wall -o $@ $<

$(KERNEL_PATH)/%.o: $(KERNEL_PATH)/%.s
	as -o $@ $<

kernel_clean:
	rm -f $(KERNEL_PATH)/*.o $(KERNEL_PATH)/kernel.bin

