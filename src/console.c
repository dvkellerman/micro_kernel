#include "console.h"
#include "types.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_SIZE (VGA_HEIGHT * VGA_WIDTH)

static volatile u16 *const vga_buffer = (volatile u16 *)0xB8000;

static size_t row = 0;
static size_t column = 0;
static u8 color = 0x07; // Light gray on black

static u8 console_entry_color(console_color fg, console_color bg) {
  return fg | bg << 4;
}

static u16 console_entry(unsigned char uc, u8 color) {
  return (u16)uc | (u16)color << 8;
}

void console_set_colors(console_color fg, console_color bg) {
  color = console_entry_color(fg, bg);
}

void console_set_foreground(console_color fg) { color = (color & 0xF0) | fg; }

void console_set_background(console_color bg) {
  color = (color & 0x0F) | (bg << 4);
}

void console_clear() {
  for (size_t i = 0; i < VGA_SIZE; i++) {
    vga_buffer[i] = console_entry(' ', color);
  }
}

void console_set_cursor(size_t x, size_t y) {
  row = x % VGA_WIDTH;
  column = y % VGA_HEIGHT;
}

static void console_put_char_at(char c, u8 color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  vga_buffer[index] = console_entry(c, color);
}

void console_put_char(char c) {
  console_put_char_at(c, color, column, row);

  if (++column == VGA_WIDTH) {
    column = 0;
    if (++row == VGA_HEIGHT) {
      row = 0;
    }
  }
}

void console_put_string(const char *str) {
  for (size_t i = 0; str[i] != '\0'; i++) {
    console_put_char(str[i]);
  }
}

// Simple printf implementation for kernel use
void console_printf(const char *format, ...) {
  va_list args;
  va_start(args, format);

  while (*format != '\0') {
    if (*format == '%') {
      format++;
      switch (*format) {
      case 's': {
        const char *str = va_arg(args, const char *);
        console_put_string(str);
        break;
      }
      // TODO:  Add more format specifiers as needed
      default:
        console_put_char(*format);
      }
    } else {
      console_put_char(*format);
    }
    format++;
  }

  va_end(args);
}
