#include <stdint.h>

/* ---- UEFI basic types ---- */
typedef void* EFI_HANDLE;
typedef uint64_t EFI_STATUS;
typedef uint16_t CHAR16;

typedef struct {
    EFI_STATUS (*Reset)(void*, int);
    EFI_STATUS (*OutputString)(void*, CHAR16*);
    EFI_STATUS (*TestString)(void*, CHAR16*);
    EFI_STATUS (*QueryMode)(void*, uint64_t, uint64_t*, uint64_t*);
    EFI_STATUS (*SetMode)(void*, uint64_t);
    EFI_STATUS (*SetAttribute)(void*, uint64_t);
    EFI_STATUS (*ClearScreen)(void*);
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct {
    char _pad[64];
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut;
} EFI_SYSTEM_TABLE;

/* ---- Colors ---- */
#define EFI_BLACK      0x00
#define EFI_RED        0x04
#define EFI_LIGHTGRAY  0x07
#define EFI_WHITE      0x0F
#define EFI_TEXT_ATTR(fg, bg) ((bg << 4) | fg)

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {
    (void)ImageHandle;

    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* out = SystemTable->ConOut;

    // Clear screen
    out->ClearScreen(out);

    // Set color: white text on red background (Max energy)
    out->SetAttribute(out, EFI_TEXT_ATTR(EFI_WHITE, EFI_RED));

    CHAR16 msg[] = L"  MERCURY OS  \r\n\r\n";
    out->OutputString(out, msg);

    // Switch to light gray on black
    out->SetAttribute(out, EFI_TEXT_ATTR(EFI_LIGHTGRAY, EFI_BLACK));

    CHAR16 msg2[] = L"UEFI boot successful.\r\n"
                    L"x86-64 | No GRUB | No BIOS\r\n"
                    L"Engine running. Waiting...\r\n";
    out->OutputString(out, msg2);

    for (;;) {
        __asm__ __volatile__("hlt");
    }

    return 0;
}
