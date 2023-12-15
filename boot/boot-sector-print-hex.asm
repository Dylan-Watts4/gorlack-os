print_hex:
	pusha

	mov cx, 0	; index value

; Get last char of 'dx' then convert to ASCII
hex_loop:
	cmp cx, 4	; loop 4 times
	je end

	; (1) convert last char of 'dx' to ASCII
	mov ax, dx
	and ax, 0x000f ; make first three values to 0
	add al, 0x30
	cmp al, 0x39
	jle step2
	add al, 7

step2:
	; (2) get the correct position of string to place our ASCII char
	; bx <- base address + string length - index of char
	mov bx, HEX_OUT + 5
	sub bx, cx
	mov [bx], al
	ror dx, 4

	add cx, 1
	jmp hex_loop

end:
	mov bx, HEX_OUT
	call print

	popa
	ret

HEX_OUT:
	db '0x0000', 0