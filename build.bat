@echo off
setlocal enabledelayedexpansion

echo INFO: Building MercuryOS 

REM ---- Directories ----
set BUILD=build
set ISO=%BUILD%\iso
set EFI_DIR=%ISO%\EFI\BOOT

REM ---- Sources ----
set KERNEL_SRC=src\kernel.c
set CONSOLE_SRC=utils\console.c
set KEYBOARD_SRC=utils\keyboard.c

REM ---- Objects (ALL in build/) ----
set KERNEL_OBJ=%BUILD%\kernel.o
set CONSOLE_OBJ=%BUILD%\console.o
set KEYBOARD_OBJ=%BUILD%\keyboard.o

REM ---- Output ----
set EFI_BIN=%EFI_DIR%\BOOTX64.EFI
set OVMF=utils\OVMF.fd

REM ---- Create directories ----
if not exist %BUILD% mkdir %BUILD%
if not exist %EFI_DIR% mkdir %EFI_DIR%

REM ---- Compile ----
echo INFO: [1/2] Compiling sources

gcc -c %KERNEL_SRC% ^
  -ffreestanding ^
  -fno-stack-protector ^
  -fno-asynchronous-unwind-tables ^
  -mno-red-zone ^
  -O2 ^
  -Wall -Wextra ^
  -Iutils ^
  -o %KERNEL_OBJ%

if errorlevel 1 goto fail

gcc -c %CONSOLE_SRC% ^
  -ffreestanding ^
  -fno-stack-protector ^
  -fno-asynchronous-unwind-tables ^
  -mno-red-zone ^
  -O2 ^
  -Wall -Wextra ^
  -Iutils ^
  -o %CONSOLE_OBJ%

if errorlevel 1 goto fail

gcc -c %KEYBOARD_SRC% ^
  -ffreestanding ^
  -fno-stack-protector ^
  -fno-asynchronous-unwind-tables ^
  -mno-red-zone ^
  -O2 ^
  -Wall -Wextra ^
  -Iutils ^
  -o %KEYBOARD_OBJ%

if errorlevel 1 goto fail

REM ---- Link ----
echo INFO: [2/2] Linking UEFI executable

ld ^
  %KERNEL_OBJ% ^
  %CONSOLE_OBJ% ^
  %KEYBOARD_OBJ% ^
  -nostdlib ^
  --subsystem=10 ^
  --entry=efi_main ^
  -o %EFI_BIN%

if errorlevel 1 goto fail

echo INFO: Build successful!

REM ---- Run in QEMU (UEFI) ----
echo INFO: Launching MercuryOS in QEMU...
qemu-system-x86_64 ^
  -bios %OVMF% ^
  -drive file=fat:rw:%ISO%,format=raw

exit /b 0

:fail
echo ERROR: Build failed!
pause
exit /b 1
