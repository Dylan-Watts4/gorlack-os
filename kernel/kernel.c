#include "../drivers/ports.h"

void main() {
	/* Screen cursor position: ask VGA control register (0x3d4) for bytes 
	   14 = high byte of cursor and 15 = low byte of cursor. */
	port_byte_out(0x3d4, 14); // Requesting byte 14: high byte of cursor pos
	// Data is returned in VGA data register (0x3d5)
	int position = port_byte_in(0x3d5);
	position = position << 8; // High byte: left shift by 8 bits

	port_byte_out(0x3d4, 15); // Requesting byte 15: low byte of cursor pos
	position += port_byte_in(0x3d5);

	// VGA 'cells' consist of character and attribute bytes
	int offset_from_vga = position * 2; // Each character is 2 bytes: char and attribute

	char *vga = 0xb8000; // VGA address starts here
	vga[offset_from_vga] = 'X'; // Character byte
	vga[offset_from_vga + 1] = 0x0f; // Attribute byte: white on black
}