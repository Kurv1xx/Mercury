SHELL := cmd.exe
.SHELLFLAGS := /c

BUILD = build
SRC   = src

BOOT_BIN   = $(BUILD)\boot.bin
ENTRY_O    = $(BUILD)\entry.o
KERNEL_O   = $(BUILD)\kernel.o
KERNEL_ELF = $(BUILD)\kernel.elf
KERNEL_BIN = $(BUILD)\kernel.bin
OS_BIN     = $(BUILD)\os.bin

all: $(OS_BIN)
	qemu-system-i386 -drive format=raw,file=$(OS_BIN),if=floppy

$(BUILD):
	if not exist $(BUILD) mkdir $(BUILD)

# -------------------------------
# Bootloader (raw 512-byte sector)
# -------------------------------
$(BOOT_BIN): $(SRC)\boot.asm | $(BUILD)
	nasm -f bin $< -o $@

# -------------------------------
# Kernel entry (ELF object)
# -------------------------------
$(ENTRY_O): $(SRC)\entry.asm | $(BUILD)
	nasm -f elf32 $< -o $@

# -------------------------------
# Kernel C (ELF object)
# -------------------------------
$(KERNEL_O): $(SRC)\kernel.c | $(BUILD)
	i686-elf-gcc -m16 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -O0 -c $< -o $@

# -------------------------------
# Link kernel at 0x1000 using linker.ld
# -------------------------------
$(KERNEL_ELF): $(ENTRY_O) $(KERNEL_O)
	i686-elf-ld -T $(SRC)\linker.ld -nostdlib -o $@ $^

# -------------------------------
# Convert kernel ELF → flat binary
# -------------------------------
$(KERNEL_BIN): $(KERNEL_ELF)
	i686-elf-objcopy -O binary $< $@

# -------------------------------
# Final floppy image
# -------------------------------
$(OS_BIN): $(BOOT_BIN) $(KERNEL_BIN)
	cmd /c "copy /b $(BOOT_BIN)+$(KERNEL_BIN) $(OS_BIN)"

clean:
	if exist $(BUILD) rmdir /s /q $(BUILD)
