CC = gcc
CFLAGS = -ffreestanding -m32 -g -fno-stack-protector -Wall -Wextra \
         -fno-pic -fno-pie -nostdlib -nodefaultlibs -fno-builtin
LDFLAGS = -Wl,--nmagic,--orphan-handling=warn,--build-id=none

SRCS = src/kernel.c src/console.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: kernel

kernel: $(OBJS)
	$(CC) -T src/kernel.ld -o $@ $(OBJS) $(CFLAGS) $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -rf kernel* kernel.iso
	rm -rf iso_dir

.PHONY: iso
iso: kernel
	mkdir -p iso_dir
	mkdir -p iso_dir/boot/grub/
	cp kernel iso_dir/boot/
	cp grub.cfg iso_dir/boot/grub/
	grub-mkrescue -o kernel.iso iso_dir

.PHONY: run
run: iso
	qemu-system-x86_64 -cdrom kernel.iso -debugcon stdio -vga virtio -m 4G -machine "q35" -no-reboot -no-shutdown

