/**
 * @file write.c
 * @author Arthur
 * @brief Permet de définir l'appel système write.
 * @version 0.2
 * @date 2026-04-10
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <unistd.h>

// Définition de l'appel système write
syscall2(int, write, const char *, s, int, len)