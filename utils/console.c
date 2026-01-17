#include "console.h"

static EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* out;

void console_init(EFI_SYSTEM_TABLE* SystemTable) {
    out = SystemTable->ConOut;
}

void console_clear(void) {
    out->ClearScreen(out);
}

void console_set_color(uint64_t attr) {
    out->SetAttribute(out, attr);
}

void console_print(CHAR16* str) {
    out->OutputString(out, str);
}
