/**
 * @file time.h
 * @brief Interface de gestion du temps et du contrôleur d'intervalle (PIT).
 */

#ifndef _TIME_H
#define _TIME_H

#include <inttypes.h>

/* --- Registres du PIT (Programmable Interval Timer) --- */
#define CHANNEL0 0x40   /**< Port de données du Canal 0 */
#define CHANNEL1 0x41   /**< Port de données du Canal 1 */
#define CHANNEL2 0x42   /**< Port de données du Canal 2 */
#define REGISTRECC 0x43 /**< Registre de commande (Mode Control) */

/* --- Fréquences et PIC --- */
#define HORLOGE 0x3E8 /**< Fréquence cible en Hz (ex: 1000 Hz pour 1ms) */
#define FREQOSC                                                                \
  0x1234BD           /**< Fréquence de l'oscillateur interne (1.193182 MHz) */
#define PICCOM 0x20  /**< Registre de commande du PIC Maître */
#define PICDATA 0x21 /**< Registre de données du PIC Maître */

/**
 * @struct heure_t
 * @brief Structure représentant le temps formaté en heures/minutes/secondes.
 */
typedef struct {
  uint32_t sec;  /**< Secondes (0-59) */
  uint32_t min;  /**< Minutes (0-59) */
  uint32_t hour; /**< Heures écoulées depuis le démarrage */
} heure_t;

/**
 * @brief Initialise le timer système (PIT).
 * Configure le matériel pour générer des interruptions à la fréquence définie.
 */
void init_timer();

/**
 * @brief Incrémente le compteur de "ticks" du système.
 * Cette fonction est généralement appelée sous interruption (IRQ0).
 */
void incremente_timer();

/**
 * @brief Récupère la valeur actuelle du compteur de ticks système.
 * @return uint32_t Le nombre de ticks écoulés depuis le boot.
 */
uint32_t get_timer();

/**
 * @brief Convertit les ticks système en une structure de temps lisible.
 * @return Une structure heure_t contenant l'heure, les minutes et les secondes.
 */
heure_t convert_timer();

/**
 * @brief Gère l'affichage périodique de l'heure.
 * Typiquement appelée pour rafraîchir l'horloge à l'écran toutes les secondes.
 */
void display_time();

#endif // _TIME_H