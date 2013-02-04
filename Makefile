#
# Makefile for ChikenOS
#

.PHONY: all clean floppy test

all: floppy

init:
	@mkdir -p build

KERNEL_PATH = sys
LIBC_PATH = libc

GLOBAL_GCC_OPTS = -std=gnu11 -Wall -Wextra -pedantic

# Include kernel make file
include $(KERNEL_PATH)/make.inc

# Include libc make file
include $(LIBC_PATH)/make.inc

floppy: init build/kernel.bin menu.lst
	@./make_floppy.sh

test: floppy
	@./test_in_qemu.sh

clean: kernel_clean libc_clean
	rm -rf build libc.a
