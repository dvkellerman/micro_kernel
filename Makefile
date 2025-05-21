.PHONY: all
all: build

build: ./src/kernel.zig ./src/console.zig ./src/kernel.ld
	zig build-exe ./src/kernel.zig \
		-target x86-freestanding \
		-T ./src/kernel.ld \
		-femit-bin=./kernel \
		-O Debug\
		-fno-strip

.PHONY: iso
iso: build
	mkdir -p iso_dir
	mkdir -p iso_dir/boot/grub/
	cp kernel iso_dir/boot/
	cp grub.cfg iso_dir/boot/grub/
	grub-mkrescue -o kernel.iso iso_dir

.PHONY: run
run: iso
	qemu-system-x86_64 -cdrom kernel.iso -debugcon stdio -vga virtio -m 4G -machine "q35" -no-reboot -no-shutdown

.PHONY: clean
clean:
	rm -rf kernel* kernel.iso
	rm -rf iso_dir
