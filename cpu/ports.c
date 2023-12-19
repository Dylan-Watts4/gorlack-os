#include "ports.h"

// Read a byte from the specified port
uint8_t port_byte_in(uint16_t port) {
    // "=a" (result) means: put AL register in variable RESULT when finished
    // "d" (port) means: load EDX with port
    uint8_t result;
    asm("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out(uint16_t port, uint8_t data) {
    // As there is no = there will be no return value
    // "a" (data) means: load EAX with data
    // "d" (port) means: load EDX with port
    asm volatile("out %%al, %%dx" : :"a" (data), "d" (port));
}

uint16_t port_word_in(uint16_t port) {
    uint16_t result;
    asm("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out(uint16_t port, uint16_t data) {
    asm volatile("out %%ax, %%dx" : :"a" (data), "d" (port));
}