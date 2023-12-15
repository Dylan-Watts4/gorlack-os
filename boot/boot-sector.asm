[org 0x7c00]
	mov bp, 0x8000
	mov sp, bp

	mov bx, 0x9000
	mov dh, 2

	call disk_load

	mov dx, [0x9000]
	call print_hex

	call print_nl

	mov dx, [0x9000 + 512]
	call print_hex

	jmp $

%include "boot-sector-print.asm"
%include "boot-sector-print-hex.asm"
%include "boot-sector-disk.asm"

times 510 - ($0$$) db 0
dw 0xaa55

times 256 dw 0xdada
times 256 dw 0xface