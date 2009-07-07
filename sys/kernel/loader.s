.globl loader 
 
.set FLAGS    , 0
.set MAGIC    , 0x1BADB002       # Magic number for GRUB
.set CHECKSUM , -(MAGIC + FLAGS) # Checksum
 
.section .text
.align 4
MultiBootHeader:
	.long MAGIC       # Magic number
	.long FLAGS       # Flags
	.long CHECKSUM    # Checksum
 
loader:
	mov $0x20000, %esp
	push %eax
	push %ebx
	call kmain
 
	cli # should never be reached
	hlt
