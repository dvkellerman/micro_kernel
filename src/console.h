#pragma once
#include "types.h"

typedef enum {
  CONSOLE_COLOR_BLACK = 0,
  CONSOLE_COLOR_BLUE = 1,
  CONSOLE_COLOR_GREEN = 2,
  CONSOLE_COLOR_CYAN = 3,
  CONSOLE_COLOR_RED = 4,
  CONSOLE_COLOR_MAGENTA = 5,
  CONSOLE_COLOR_BROWN = 6,
  CONSOLE_COLOR_LIGHT_GRAY = 7,
  CONSOLE_COLOR_DARK_GRAY = 8,
  CONSOLE_COLOR_LIGHT_BLUE = 9,
  CONSOLE_COLOR_LIGHT_GREEN = 10,
  CONSOLE_COLOR_LIGHT_CYAN = 11,
  CONSOLE_COLOR_LIGHT_RED = 12,
  CONSOLE_COLOR_LIGHT_MAGENTA = 13,
  CONSOLE_COLOR_YELLOW = 14,
  CONSOLE_COLOR_WHITE = 15,
} console_color;

void console_set_colors(console_color fg, console_color bg);
void console_clear(void);
void console_put_string(const char *str);
void console_set_foreground(console_color fg);
void console_put_char(char c);
