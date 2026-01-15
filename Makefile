SHELL := cmd.exe
.SHELLFLAGS := /c

# Toolchain
CC = riscv-none-elf-gcc

# Paths
SRC   = src
BUILD = build

# Outputs
ENTRY_O   = $(BUILD)\entry.o
KERNEL_O  = $(BUILD)\kernel.o
KERNEL_ELF = $(BUILD)\kernel.elf

# Architecture flags
ARCH_FLAGS = -march=rv64imac -mabi=lp64 -mcmodel=medany
CFLAGS  = -ffreestanding -nostdlib -O0 $(ARCH_FLAGS)
LDFLAGS = -T $(SRC)\linker.ld -nostdlib $(ARCH_FLAGS)

# Default target
all: $(KERNEL_ELF)
	qemu-system-riscv64 -machine virt -device virtio-gpu-pci -display gtk -serial stdio -monitor none -kernel $(KERNEL_ELF)

# Build directory
$(BUILD):
	if not exist $(BUILD) mkdir $(BUILD)

# Entry (ASM)
$(ENTRY_O): $(SRC)\entry.S | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# Kernel (C)
$(KERNEL_O): $(SRC)\kernel.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# Link kernel
$(KERNEL_ELF): $(ENTRY_O) $(KERNEL_O)
	$(CC) $(LDFLAGS) -o $@ $^

# Clean
clean:
	if exist $(BUILD) rmdir /s /q $(BUILD)
