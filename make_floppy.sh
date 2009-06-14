#!/bin/sh

#
# Mount floppy file
#
mkdir /tmp/floppy
echo "Mounting floppy image, root required..."
sudo mount -o loop floppy.img /tmp/floppy/
cp sys/kernel/kernel.bin /tmp/floppy/
mkdir /tmp/floppy/grub

#
# Copy GRUB and ChikenOS menu.lst to floppy
#
cp /boot/grub/stage1 /tmp/floppy/grub
cp /boot/grub/stage2 /tmp/floppy/grub
cp menu.lst /tmp/floppy/grub/menu.lst
sudo umount /tmp/floppy/
rmdir /tmp/floppy

#
# Set up GRUB
#
/usr/sbin/grub --batch 2> /dev/null > /dev/null << EOF
device (fd0) floppy.img
root (fd0)
setup (fd0)
EOF

