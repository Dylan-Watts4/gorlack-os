[org 0x7c00]
KERNEL_OFFSET equ 0x1000

	mov [BOOT_DRIVE], d1	; BIOS sets us the boot drive in 'd1' on boot
	mov bp, 0x9000
	mov sp, bp

	mov bx, MSG_REAL_MODE
	call print
	call print_nl

	call load_kernel		; Read the kernel from disk
	call switch_to_pm		; Disable interrupts, load GDT, etc
	jmp $					; Never executed

%include "boot/print.asm"
%include "boot/print-hex.asm"
%include "boot/disk.asm"
%include "boot/gdt.asm"
%include "boot/32bit-print.asm"
%include "boot/switch-pm.asm"

[bits 16]
load_kernel:
	mov bx, MSG_LOAD_KERNEL
	call print
	call print_nl

	mov bx, KERNEL_OFFSET	; Read from disk and store in 0x1000
	mov dh, 16				; Our future kernel will be larger
	mov dl, [BOOT_DRIVE]
	call disk_load
	ret

[bits 32]
BEGIN_PM:
	mov ebx, MSG_PROT_MODE
	call print_string_pm
	call KERNEL_OFFSET		; Give control to the kernel
	jmp $					; Stay here when kernel returns control

BOOT_DRIVE db 0				; Store in memory as 'dl' may get overwriten
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE db "Landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

; Padding
times 510 - ($-$$) db 0
dw 0xaa55