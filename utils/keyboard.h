#pragma once
#include "uefi.h"

void keyboard_init(EFI_SYSTEM_TABLE* SystemTable);
int  keyboard_read(CHAR16* out);
