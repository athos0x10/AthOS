#include <n7OS/console.h>
#include <../include/debug.h>

/* Variable to stock the screen adress */
uint16_t *scr_tab;
/* Actual position in the screen (cursor) */
uint16_t pos;

void init_console() {
    // Set the pointer of the screen
    scr_tab= (uint16_t *) SCREEN_ADDR;
    // Initilisation of the position.
    pos = 0u;
}

void console_putchar(const char c) {
    // ASCII Character
    if ((c > 31u) && (c < 127u)) { 
        scr_tab[pos]= CHAR_COLOR<<8 | c;
        pos++;
    }
    // Line Feed
    else if (c == '\n') {
        pos += (VGA_WIDTH - (pos % VGA_WIDTH));
    }
    // Carriage Return 
    else if (c == '\r') {
        pos -= (pos % VGA_WIDTH);
    }
    // Horizontal Tab 
    else if (c == '\t') {
        for (uint8_t i = 0u; i < 8u; i++) {
            scr_tab[pos] = CHAR_COLOR<<8 | ' ';
            pos++;
        }
    }
    // Backspace
    else if (c == '\b') {
        if (pos > 0u) {
            pos--;
        }
    }
    // Form Feed
    else if (c == '\f') {
        for (uint16_t i = 0u; i < (VGA_WIDTH * VGA_HEIGHT); i ++) {
            scr_tab[i] = CHAR_COLOR<<8 | ' ';
        }
        pos = 0u;
    }

    // Ensure pos does not overflow
    if (pos >= VGA_WIDTH * VGA_HEIGHT) {
        pos = (VGA_HEIGHT - 1) * VGA_WIDTH;
    }
}

void console_putbytes(const char *s, int len) {
    for (int i= 0; i<len; i++) {
        console_putchar(s[i]);
    }
}