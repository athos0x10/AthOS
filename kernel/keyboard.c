#include <n7OS/cpu.h>
#include <n7OS/keyboard.h>

// Buffer for storing keystrokes
char keyboard_buffer[KEYBOARD_BUFFER_SIZE];
// Index for the keyboard buffer (used for both start and end)
uint16_t keyboard_buffer_index_start = 0u;
uint16_t keyboard_buffer_index_end = 0u;
// Shift state
uint8_t shift_state = 0u;

void init_keyboard() {
  // Initialize the keyboard IT
  outb(inb(0x21) & ~(KEYB_CTRL_IN_BUF), 0x21);

  // Initialize the keyboard buffer
  for (uint16_t i = 0; i < KEYBOARD_BUFFER_SIZE; i++) {
    keyboard_buffer[i] = '\0';
  }

  keyboard_buffer_index_start = 0u;
  keyboard_buffer_index_end = 0u;
}

char kgetch() {
  char c = '\0';

  if (keyboard_buffer_index_start != keyboard_buffer_index_end) {
    c = keyboard_buffer[keyboard_buffer_index_start];
    keyboard_buffer[keyboard_buffer_index_start] =
        '\0'; // Clear the buffer slot
    keyboard_buffer_index_start =
        (keyboard_buffer_index_start + 1) %
        KEYBOARD_BUFFER_SIZE; // Move to the next index
  }

  return c;
}