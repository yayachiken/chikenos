#
# Makefile for ChikenOS
#

all: floppy

floppy: kernel
	dd if=/dev/zero of=floppy.img bs=1024 count=1440 > /dev/null 2> /dev/null
	/sbin/mke2fs -F floppy.img > /dev/null 2> /dev/null
	./make_floppy.sh

kernel: libc force
	make -C sys/kernel kernel.bin

libc: force
	make -C libc libc.a

clean:
	rm -f floppy.img
	make -C sys/kernel clean
	make -C libc clean

force:
	true

