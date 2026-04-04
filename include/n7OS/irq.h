#ifndef __IRQ_H__
#define __IRQ_H__

#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <n7OS/segment.h>

/*
Une entrée dans l'IDT est sur 64 bits

Partie poids forts
Bit :     | 31              16 | 15 | 14 13 | 12 | 11 10 9 8 | 7 6 5 | 4 3 2 1 0
| Contenu : | offset supérieur   | P  | DPL   | S  | GateType  | 0 0 0 | réservé
|

Partie poids faible
Bit :     | 31              16 | 15              0 |
Contenu : |sélecteur de segment| offset inférieur  |
*/

#define PRESENTI 0b10000000
#define DPL_HIGH 0b00000000
#define INTERUPT_GATE 0b00000000
#define INT_GATE32 0b00001110

typedef struct {
  uint16_t offset_inf;
  uint16_t sel_segment;
  uint8_t zero;
  uint8_t type_attr;
  uint16_t offset_sup;
} idt_entry_t;

/**
 * @brief Crée une entrée dans la table d'interuption pour une IRQ donnée.
 *
 * @param irq_num Le numéro de l'IRQ.
 * @param addr L'adresse de la fonction qui gère l'IRQ.
 */
void init_irq_entry(int irq_num, uint32_t addr);

#endif
