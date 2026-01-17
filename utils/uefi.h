#pragma once
#include <stdint.h>

/* ---- UEFI basic types ---- */
typedef void*    EFI_HANDLE;
typedef uint64_t EFI_STATUS;
typedef uint16_t CHAR16;

/* ---- EFI Table Header ---- */
typedef struct {
    uint64_t Signature;
    uint32_t Revision;
    uint32_t HeaderSize;
    uint32_t CRC32;
    uint32_t Reserved;
} EFI_TABLE_HEADER;

/* ---- Simple Text Input ---- */
typedef struct {
    uint16_t ScanCode;
    CHAR16   UnicodeChar;
} EFI_INPUT_KEY;

typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
    EFI_STATUS (*Reset)(
        struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL* This,
        int ExtendedVerification
    );

    EFI_STATUS (*ReadKeyStroke)(
        struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL* This,
        EFI_INPUT_KEY* Key
    );

    void* WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

/* ---- Simple Text Output ---- */
typedef struct {
    EFI_STATUS (*Reset)(void*, int);
    EFI_STATUS (*OutputString)(void*, CHAR16*);
    EFI_STATUS (*TestString)(void*, CHAR16*);
    EFI_STATUS (*QueryMode)(void*, uint64_t, uint64_t*, uint64_t*);
    EFI_STATUS (*SetMode)(void*, uint64_t);
    EFI_STATUS (*SetAttribute)(void*, uint64_t);
    EFI_STATUS (*ClearScreen)(void*);
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

/*
 * ---- EFI_SYSTEM_TABLE (REAL LAYOUT, NO GUESSING) ----
 */
typedef struct {
    EFI_TABLE_HEADER                Hdr;

    CHAR16*                         FirmwareVendor;
    uint32_t                        FirmwareRevision;

    EFI_HANDLE                      ConsoleInHandle;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL* ConIn;

    EFI_HANDLE                      ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut;

    EFI_HANDLE                      StandardErrorHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* StdErr;
} EFI_SYSTEM_TABLE;
