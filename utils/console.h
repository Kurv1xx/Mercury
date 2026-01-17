#pragma once
#include "uefi.h"

/* ---- Colors ---- */
#define EFI_BLACK      0x00
#define EFI_RED        0x04
#define EFI_LIGHTGRAY  0x07
#define EFI_WHITE      0x0F
#define EFI_TEXT_ATTR(fg, bg) ((bg << 4) | fg)

/* ---- Console API ---- */
void console_init(EFI_SYSTEM_TABLE* SystemTable);
void console_clear(void);
void console_set_color(uint64_t attr);
void console_print(CHAR16* str);
