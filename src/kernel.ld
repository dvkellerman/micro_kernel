ENTRY(_start)

PHDRS {
    text PT_LOAD FLAGS(5); /* Read + Execute */
    data PT_LOAD FLAGS(6); /* Read + Write */
}

SECTIONS {
         . = 1M;

         .text : ALIGN(4K) {
               KEEP(*(.multiboot))
               *(.text)
         } :text

         .rodata : ALIGN(4K) {
               *(.rodata)
         } :data

         .bss : ALIGN(4K) {
               *(.bss)
         } :data

         .data : ALIGN(4k) {
                *(.data)
         } :data

        .debug_info : ALIGN(4k)  {
            *(.debug_info)
        }

        .debug_abbrev : ALIGN(4k) {
            *(.debug_abbrev)
        }

}
