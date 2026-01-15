#define UART0 0x10000000UL

static inline void uart_putc(char c) {
    *(volatile unsigned char *)UART0 = (unsigned char)c;
}

void kernel_main(void) {
    const char *msg = "Mercury (RISC-V) is alive...\n";

    for (int i = 0; msg[i]; i++) {
        uart_putc(msg[i]);
    }
    uart_putc('K');
    uart_putc('\n');

    while (1) {}
}
