#include <n7OS/console.h>
#include <n7OS/cpu.h>
#include <../include/debug.h>

/* Variable to stock the screen adress */
uint16_t *scr_tab;
/* Actual lign in the screen */
uint16_t lign;
/* Actual column in the screen */
uint16_t column;

void init_console() {
    // Set the pointer of the screen
    scr_tab= (uint16_t *) SCREEN_ADDR;
    // Clear the screen
    console_clear_screen();
    // Init of lign and column
    lign = 0u;
    column = 0u;
    // Set the cursor position
    console_update_cursor();
}

void console_clear_screen() {
    for (uint16_t i = 0u; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        // Replace the actual value by a space
        scr_tab[i] = CHAR_COLOR << 8 | ' ';
    }
}

void console_update_cursor() {
    // Update the hardware cursor
    uint16_t cursor_pos = (lign * VGA_WIDTH) + column;
    outb(CMD_LOW, PORT_CMD);
    outb(cursor_pos & 255, PORT_DATA);
    outb(CMD_HIGH, PORT_CMD);
    outb(cursor_pos >> 8, PORT_DATA);
}

void console_putchar(const char c) {
    // ASCII Character
    if ((c > 31u) && (c < 127u)) { 
        scr_tab[lign]= CHAR_COLOR<<8 | c;
        lign++;
    }
    // Line Feed
    else if (c == '\n') {
        lign += (VGA_WIDTH - (lign % VGA_WIDTH));
    }
    // Carriage Return 
    else if (c == '\r') {
        lign -= (lign % VGA_WIDTH);
    }
    // Horizontal Tab 
    else if (c == '\t') {
        for (uint8_t i = 0u; i < 8u; i++) {
            scr_tab[lign] = CHAR_COLOR<<8 | ' ';
            lign++;
        }
    }
    // Backspace
    else if (c == '\b') {
        if (lign > 0u) {
            lign--;
        }
    }
    // Form Feed
    else if (c == '\f') {
        console_clear_screen();
    }
    // Ensure lign does not overflow
    if (lign >= VGA_WIDTH * VGA_HEIGHT) {
        lign = (VGA_HEIGHT - 1) * VGA_WIDTH;
    }
    //Update the cursor
    console_update_cursor();
}

void console_putbytes(const char *s, int len) {
    for (int i= 0; i<len; i++) {
        console_putchar(s[i]);
    }
}