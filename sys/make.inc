#
# Makefile for the ChikenOS kernel
#

LIBC_INCLUDE_PATH = libc/include
KERNEL_INCLUDE_PATH = $(KERNEL_PATH)/include
KERNEL_SRC_PATH = $(KERNEL_PATH)/kernel

KERNEL_OBJ = 	$(KERNEL_SRC_PATH)/loader.o \
		$(KERNEL_SRC_PATH)/kmain.o \
		$(KERNEL_SRC_PATH)/console.o \
		$(KERNEL_SRC_PATH)/gdt.o \
		$(KERNEL_SRC_PATH)/interrupt.o \
		$(KERNEL_SRC_PATH)/pic.o

build/kernel.bin: $(KERNEL_OBJ) libc.a
	ld -m elf_i386 -T $(KERNEL_SRC_PATH)/ld.conf -o $@ $+

$(KERNEL_SRC_PATH)/%.o: $(KERNEL_SRC_PATH)/%.c
	@$(CC) -c -m32 -I$(LIBC_INCLUDE_PATH) -I$(KERNEL_INCLUDE_PATH) $(GLOBAL_CC_OPTS) -o $@ $<

$(KERNEL_SRC_PATH)/%.o: $(KERNEL_SRC_PATH)/%.S
	@as --32 -march=i386 -o $@ $<

kernel_clean:
	rm -f $(KERNEL_SRC_PATH)/*.o $(KERNEL_SRC_PATH)/kernel.bin

