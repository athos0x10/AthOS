# Compatible macOS (Homebrew) + Linux
OS := $(shell uname -s)

# Si x86_64-elf-gcc existe, on l'utilise
ifneq ($(shell which x86_64-elf-gcc 2>/dev/null),)
    PREFIX := x86_64-elf-
# Sinon si i386-elf-gcc existe on l'utilise
else ifneq ($(shell which i386-elf-gcc 2>/dev/null),)
    PREFIX := i386-elf-
# Sinon erreur
else
    $(error No ELF cross-compiler found. Install x86_64-elf-gcc or i386-elf-gcc)
endif

GCC_PATH := $(shell which $(PREFIX)gcc)
GCC_DIR  := $(shell dirname $(GCC_PATH))

CC      := $(PREFIX)gcc
AS      := $(PREFIX)gcc
LD      := $(PREFIX)ld
OBJCOPY := $(PREFIX)objcopy
DEBUG   := $(PREFIX)gdb

CFLAGS  := -m32 -g -ggdb -std=c99 \
           -nostdlib -nostdinc \
           -fno-builtin -fno-stack-protector \
           -nostartfiles -nodefaultlibs \
           -Wall -Wextra

ASFLAGS := -m32 -DASSEMBLER -g -ggdb

LDFLAGS := -m elf_i386