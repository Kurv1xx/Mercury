SHELL := cmd.exe
.SHELLFLAGS := /c


CC := riscv-none-elf-gcc
SRC := src
BUILD := build

ENTRY_SRC := $(SRC)\entry.s
KERNEL_SRC := $(SRC)\kernel.c
LINKER := $(SRC)\linker.ld

ENTRY_O := $(BUILD)\entry.o
KERNEL_O := $(BUILD)\kernel.o
KERNEL_ELF := $(BUILD)\kernel.elf

ARCH := -march=rv64imac -mabi=lp64 -mcmodel=medany
CFLAGS := -ffreestanding -nostdlib -O0 $(ARCH)
LDFLAGS := -T $(LINKER) -nostdlib $(ARCH)


all: $(KERNEL_ELF)
	qemu-system-riscv64 -machine virt -device virtio-gpu-pci -display gtk -serial stdio -monitor none -kernel $(KERNEL_ELF)

$(BUILD):
	if not exist $(BUILD) mkdir $(BUILD)

$(ENTRY_O): $(ENTRY_SRC) | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL_O): $(KERNEL_SRC) | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL_ELF): $(ENTRY_O) $(KERNEL_O)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	if exist $(BUILD) rmdir /s /q $(BUILD)
