typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}


#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  ((uint16_t*)0xB8000)

enum vga_color {
    VGA_BLACK = 0,
    VGA_WHITE = 15,
};

static inline uint16_t vga_entry(char c, uint8_t color) {
    return (uint16_t)c | (uint16_t)color << 8;
}


static uint16_t* const vga_buffer = VGA_MEMORY;
static uint32_t cursor_pos = 0;
static uint8_t current_color = VGA_WHITE;

void vga_disable_cursor(void) {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void vga_clear(void) {
    cursor_pos = 0;
    for (uint32_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_buffer[i] = vga_entry(' ', current_color);
    }
}

void vga_putc(char c) {
    if (c == '\n') {
        cursor_pos += VGA_WIDTH - (cursor_pos % VGA_WIDTH);
        return;
    }
    vga_buffer[cursor_pos++] = vga_entry(c, current_color);
}

void vga_print(const char* str) {
    for (uint32_t i = 0; str[i]; i++) {
        vga_putc(str[i]);
    }
}

void kernel_main(void) {
    vga_disable_cursor();
    vga_clear();

    vga_print("Mercury v1.0 Online\n");
    vga_print("Status: GREEN, All Systems Operational.\n");

    for (;;) {
        __asm__ volatile ("hlt");
    }
}
