#include "timer.h"
#include "isr.h"
#include "../libc/function.h"
#include "ports.h"

uint32_t tick = 0;

static void timer_callback(registers_t *regs) {
    tick++;
    UNUSED(regs);
}

void init_timer(uint32_t freq) {
    // Firstly, register our timer callback.
    register_interrupt_handler(IRQ0, timer_callback);

    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    uint32_t divisor = 1193180 / freq;
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

    // Send the command byte.
    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}