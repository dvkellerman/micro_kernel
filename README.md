
# Micro-Kernel in C with QEMU Emulation
A lightweight micro-kernel written in C, designed to run on QEMU for emulation and testing purposes.

## Features

- **Minimalist Design**: Small, focused kernel with essential functionality
- **QEMU-Compatible**: Easy to run and test in emulated environments
- **Modular Architecture**: Components can be added or removed as needed

## Prerequisites

- GCC
- [QEMU](https://www.qemu.org/) (system emulator)
- [Grub2](https://wiki.osdev.org/GRUB#Installing_GRUB_2_on_OS_X) (bootloader)
- `i386-efl` Cross-compiler toolchain (for target architecture)
- `make` (for build automation, optional)

## Getting Started

### Build the Kernel

```sh
make
```

### Run the Kernel

```sh
make run
```
