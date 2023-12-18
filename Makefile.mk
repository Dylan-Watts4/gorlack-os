C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h)

OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

CC = /home/dylan/opt/cross/bin/i686-elf-gcc
LD = /home/dylan/opt/cross/bin/i686-elf-ld
GDB = /home/dylan/opt/cross/bin/i686-elf-gdb

CFLAGS = -g

os-image.bin: boot/boot-sector.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: boot/kernel-entry.o ${OBJ}
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/kernel-entry.o ${OBJ}
	i686-elf-ld -o $@ -Ttext 0x1000 $^

run: os-image.bin
	qemu-system-x86_64 -fda os-image.bin

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