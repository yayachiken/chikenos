#
# Makefile for ChikenOS
#

.PHONY: all clean

all: floppy

KERNEL_PATH = sys/kernel
LIBC_PATH = libc

# Include kernel make file
include $(KERNEL_PATH)/make.inc

# Include libc make file
include $(LIBC_PATH)/make.inc

floppy: kernel.bin
	@dd if=/dev/zero of=floppy.img bs=1024 count=1440 > /dev/null 2> /dev/null
	@/sbin/mke2fs -F floppy.img > /dev/null 2> /dev/null
	@./make_floppy.sh

clean: kernel_clean libc_clean
	rm -f floppy.img
