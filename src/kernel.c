#include "console.h"
#include <stdint.h>
#include <stdnoreturn.h>

int main(void);

// Multiboot header constants
#define ALIGN (1 << 0)
#define MEMINFO (1 << 1)
#define MB1_MAGIC 0x1BADB002
#define FLAGS (ALIGN | MEMINFO)

// Multiboot header structure
struct multiboot_header {
  uint32_t magic;
  uint32_t flags;
  uint32_t checksum;
};

// The Multiboot header must be in the first 8KB and aligned to 4 bytes
__attribute__((section(".multiboot"), aligned(4)))
const struct multiboot_header multiboot = {
    .magic = MB1_MAGIC,
    .flags = FLAGS,
    .checksum = -(MB1_MAGIC + FLAGS) // Checksum calculation
};

noreturn void _start(void) {
  main();
  while (1) {
  } // Infinite loop if main returns
}

int main(void) {
  // Initialize console
  console_set_colors(CONSOLE_COLOR_WHITE, CONSOLE_COLOR_BLUE);
  console_clear();

  // Print messages
  console_put_string("Hello, World from kernel!");
  console_set_foreground(CONSOLE_COLOR_LIGHT_RED);
  console_put_char('!');

  // Hang forever
  while (1) {
  }

  return 0;
}
