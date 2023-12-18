C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h)

OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

CC = /usr/bin/gcc
GDB = /usr/bin/gdb

CFLAGS = -g -m32 -fno-PIC
LDFLAGS = -no-PIE -m elf_i386

os-image.bin: boot/boot-sector.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: boot/kernel-entry.o ${OBJ}
	ld ${LDFLAGS} -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/kernel-entry.o ${OBJ}
	ld ${LDFLAGS} -o $@ -Ttext 0x1000 $^

run: os-image.bin
	qemu-system-i386 os-image.bin

debug: os-image.bin kernel.elf
	qemu-system-x86_64 -s -fda os-image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o

# TODO convert to 32 bit