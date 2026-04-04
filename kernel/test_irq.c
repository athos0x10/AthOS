#include <n7OS/irq.h>
#include <n7OS/cpu.h>
#include <stdio.h>
#include <n7OS/time.h>

extern void handler_IT();
extern void handler_IT50();
extern void handler_IT32();


void init_irq() {
    init_irq_entry(50,(uint32_t) handler_IT50);
    init_irq_entry(32,(uint32_t) handler_IT32);
}

void handler_en_C() {

}

void handler_it50() {

    printf("J'ai bien recu l'interruption 50\n");
}

void handler_it32() {
    // Désactivation de l'IT
    outb(inb(PICDATA)|1, PICDATA);

    // Ack de l'IT au PIC
    outb(0x20, 0x20);

    // Incrémentation du compteur système
    incremente_timer();

    // MaJ de l'Affichage
    display_time();

    // Activation de l'IT
    outb(inb(PICDATA) & 0xFE, PICDATA);
}
