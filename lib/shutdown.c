/**
 * @file shutdown.c
 * @author Arthur
 * @brief Permet de définir l'appel système shutdown.
 * @version 0.1
 * @date 2026-04-10
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <unistd.h>

// Définition de l'appel système shutdown
syscall1(int, shutdown, int, n)