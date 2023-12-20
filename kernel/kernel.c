#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "kernel-config.h"
#include "../drivers/pci.h"
#include <stdint.h>

uint8_t terminal_colour = 0x0F;

void kernel_main() {
	isr_install();
	irq_install();

	init_kernel();

	kprint("Type something, it will go through the kernel\n"
		"Type END to halt the CPU or PAGE to request a kmalloc()\n> ");
}

void init_kernel() {
	terminal_colour = vga_entry_colour(VGA_COLOUR_GREEN, VGA_COLOUR_BLACK);
	clear_screen();
	kprint("Welcome to GORLACK OS\n");
}

void user_input(char *input) {
	if (strcmp(input, "END") == 0) {
		kprint("Stopping the CPU. Bye!\n");
		asm volatile("hlt");
	} else if (strcmp(input, "PAGE") == 0) {
		uint32_t phys_addr;
		uint32_t page = kmalloc(1000, 1, &phys_addr);
		char page_str[16] = "";
		hex_to_ascii(page, page_str);
		char phys_str[16] = "";
		hex_to_ascii(phys_addr, phys_str);
		kprint("Page: ");
		kprint(page_str);
		kprint(", physical address: ");
		kprint(phys_str);
		kprint("\n");
	} else if (strcmp(input, "HELP") == 0) {
		kprint("No, Gorlack OS doesn't help...\n");
	} else if (strcmp(input, "PCI") == 0) {
		get_all_pci_devices();
	} else {
		kprint("Command not found: ");
		kprint(input);
		kprint("\n");
	}
	kprint("> ");
}