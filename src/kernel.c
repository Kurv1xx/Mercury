#include "console.h"
#include "keyboard.h"

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {
    (void)ImageHandle;

    console_init(SystemTable);
    keyboard_init(SystemTable);
    console_clear();
    console_print(L"BOOTED\r\n");

    while (1) {
        CHAR16 c;
        if (keyboard_read(&c)) {
            CHAR16 buf[2] = { c, 0 };
            console_print(buf);
        }
    }
}

