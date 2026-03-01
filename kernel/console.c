#include <n7OS/console.h>
#include <n7OS/cpu.h>
#include <../include/debug.h>

/* Variable to stock the screen adress */
uint16_t *scr_tab;
/* Actual row in the screen */
uint16_t row;
/* Actual column in the screen */
uint16_t column;

void init_console() {
    // Set the pointer of the screen
    scr_tab= (uint16_t *) SCREEN_ADDR;
    // Clear the screen
    console_clear_screen();
    // Init of row and column
    row = 0u;
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
    // Compute the current position
    uint16_t cursor_pos = (row * VGA_WIDTH) + column;
    // Update the hardware cursor
    outb(CMD_LOW, PORT_CMD);
    outb(cursor_pos & 255, PORT_DATA);
    outb(CMD_HIGH, PORT_CMD);
    outb(cursor_pos >> 8, PORT_DATA);
}

void console_update_pos() {
    // First we check the current column
    if (column == VGA_WIDTH) {
        row++;
        column = 0u;
    }
    // Then we check the current row
    if (row == VGA_HEIGHT) {
        //TODO scroll
    }
}

void console_put_tab() {
    uint8_t i = 0u;

    while ((i < 8u) && (column != VGA_WIDTH)) {
        console_putchar(' ');
        i++;
    }
}

void console_putchar(const char c) {
    //Compute the current position in the screen
    uint16_t current_pos = (VGA_WIDTH * row) + column;

    // ASCII Character
    if ((c > 31u) && (c < 127u)) { 
        scr_tab[current_pos]= CHAR_COLOR<<8 | c;
        column++;
    }

    // Line Feed
    else if (c == '\n') {
        row++;
        column = 0u;
    }

    // Carriage Return 
    else if (c == '\r') {
        column = 0u;
    }

    // Horizontal Tab 
    else if (c == '\t') {
        console_put_tab();
    }

    // Backspace
    else if (c == '\b') {
        // Check if there is something to erase on the current row
        if (column > 0u) {
            scr_tab[current_pos - 1u]= CHAR_COLOR<<8 | ' ';
            column--;
        } 
        // Otherwise we move up to the upper row
        else if (row > 0u) {
            row--;
            column = VGA_WIDTH - 1u;
            current_pos = (VGA_WIDTH * row) + column;
            scr_tab[current_pos]= CHAR_COLOR<<8 | ' ';
        }
    }

    // Form Feed
    else if (c == '\f') {
        // Erase the whole screen
        console_clear_screen();
        // Update values
        row = 0u;
        column = 0u;
    }
    //Update the position
    console_update_pos();
    //Update the cursor
    console_update_cursor();
}

void console_putbytes(const char *s, int len) {
    for (int i= 0; i<len; i++) {
        console_putchar(s[i]);
    }
}