typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;

#define VGA_MEMORY ((uint16_t*)0xB8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static uint16_t vga_entry(char c, uint8_t color) {
    return (uint16_t)c | (uint16_t)color << 8;
}

void clear_screen(void) {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            VGA_MEMORY[y * VGA_WIDTH + x] = vga_entry(' ', 0x07);
        }
    }
}

static inline void outb(unsigned short port, unsigned char value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

void disable_cursor(void) {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}


void kernel_main(void) {
    disable_cursor();
    clear_screen();

    const char* msg = "Mercury Kernel Alive...";
    uint8_t color = 0x0F;

    for (int i = 0; msg[i]; i++) {
        VGA_MEMORY[i] = vga_entry(msg[i], color);
    }

    while (1) {}
}
