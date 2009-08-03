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

floppy: build/kernel.bin
	@./make_floppy.sh

clean: kernel_clean libc_clean
	rm -rf build/*
