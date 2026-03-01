# Compatible macOS (Homebrew) + Linux
OS := $(shell uname -s)

# Si i686-elf-gcc existe, on l'utilise
ifneq ($(shell which i686-elf-gcc 2>/dev/null),)
    PREFIX := i686-elf-
# Sinon si i386-elf-gcc existe on l'utilise
else ifneq ($(shell which i386-elf-gcc 2>/dev/null),)
    PREFIX := i386-elf-
# Sinon erreur
else
    PREFIX :=
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