#include "keyboard.h"

static EFI_SIMPLE_TEXT_INPUT_PROTOCOL* in;

void keyboard_init(EFI_SYSTEM_TABLE* SystemTable) {
    in = SystemTable->ConIn;
    in->Reset(in, 0);
}

int keyboard_read(CHAR16* out) {
    EFI_INPUT_KEY key;

    if (in->ReadKeyStroke(in, &key) == 0) {
        if (key.UnicodeChar) {
            *out = key.UnicodeChar;
            return 1;
        }
    }
    return 0;
}
