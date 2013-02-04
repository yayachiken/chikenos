.globl loader
.globl gdt_flush
.globl int_handle
.globl int_ecode_handle
.globl test_int
 
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

gdt_flush:
	lgdt (gdtp)
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	jmp $0x08, $gdt_reload
gdt_reload:
	ret

# Other assembler functions
int_handle:
	iret

int_ecode_handle:
	add $0x4, %esp
	iret

test_int:
	push $yay
	call con_puts
	add $4, %esp
	call pic_eoi
	iret
	
yay:
	.ascii "Yay a chiken! \0"

