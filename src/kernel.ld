ENTRY(_start)

SECTIONS {
         . = 1M;

         .text : ALIGN(4K) {
               KEEP(*(.multiboot))
               *(.text)
         }

         .rodata : ALIGN(4K) {
               *(.rodata)
         }

         .data : ALIGN(4k) {
                *.(data)
         }

}
