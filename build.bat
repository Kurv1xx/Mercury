@echo off
setlocal

echo ===============================
echo Building MERCURY (UEFI x86_64)
echo ===============================

set SRC=src\kernel.c
set OBJ=kernel.o
set EFI_DIR=iso\EFI\BOOT
set EFI=%EFI_DIR%\BOOTX64.EFI

if not exist %EFI_DIR% mkdir %EFI_DIR%

echo [1/2] Compiling...
gcc -c %SRC% ^
  -ffreestanding ^
  -fno-stack-protector ^
  -fno-exceptions ^
  -fno-asynchronous-unwind-tables ^
  -mno-red-zone ^
  -O2 ^
  -Wall -Wextra ^
  -o %OBJ%

if errorlevel 1 goto fail

echo [2/2] Linking UEFI executable...
ld %OBJ% ^
  -nostdlib ^
  --subsystem=10 ^
  --entry=efi_main ^
  -o %EFI%

if errorlevel 1 goto fail

echo ===============================
echo Build SUCCESS
echo Output: %EFI%
echo ===============================

qemu-system-x86_64 -bios D:\Projects\Mercury\utils\OVMF.fd -drive file=fat:rw:iso,format=raw

pause
exit /b 0

:fail
echo BUILD FAILED
pause
exit /b 1
