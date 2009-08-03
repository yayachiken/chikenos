#!/bin/bash

dd if=/dev/zero of=build/floppy.img bs=1024 count=1440 2> /dev/null
# Create mtools config file
cat << EOF > build/mtools.conf
drive i:
	file="build/floppy.img" cylinders=80 heads=2 sectors=18 filter
EOF
export MTOOLSRC=build/mtools.conf
# Format disk
mformat i:
# Copy kernel.bin
mcopy -D o build/kernel.bin i:/kernel.bin
# Copy menu.lst
mmd -D s i:/boot
mmd -D s i:/boot/grub
mcopy -D o build/menu.lst i:/boot/grub/menu.lst
# Copy grub
mcopy -D o /boot/grub/stage? i:/boot/grub/
# Install grub
grub --batch --no-floppy <<EOF 2> /dev/null > /dev/null
	device (fd0) build/floppy.img
	root (fd0)
	setup (fd0)
EOF

rm -f build/mtools.conf
