#include <n7OS/time.h>
#include <../include/debug.h>
#include <n7OS/cpu.h>
#include <n7OS/console.h>


uint32_t timer = 0u;

void init_timer() {
    // Channel 0, accès poids faible/poids fort, générateur
    // d’impulsion, fréquence définie en binaire
    outb(0x34,REGISTRECC);

    // Calcul de la fréquence 
    uint32_t f_osc = 0x1234BD;
    uint32_t FREQUENCE = f_osc / HORLOGE;

    // Affectation de la fréquence, poids faible, au Channel 0
    outb(FREQUENCE&0xFF, 0x40);
    //Affectation de la fréquence, poids faible, au Channel 0
    outb(FREQUENCE>>8, 0x40);

    // Activation de l'IT
    outb(inb(PICDATA) & 0xFE, PICDATA);
}

void incremente_timer() {
    timer++;
}

uint32_t get_timer() {
    return timer;
}

heure_t convert_timer() {
    heure_t heure;
    uint32_t total_sec = timer / 1000u;

    heure.sec = total_sec % 60u;
    heure.min = (total_sec / 60u) % 60u;
    heure.hour = total_sec / 3600u;

    return heure;
}

void display_time() {
    heure_t heure;
    heure = convert_timer();

    if (get_timer() % 1000u == 0u) {
        print_heure(heure);
    }
}
