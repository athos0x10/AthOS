#include <n7OS/mem.h>

/* Mise en place de l'utilisation Bitmap */

/* Taille du Bitmap */
//const uint32_t SIZE = PAGE_SIZE / 32u;

/* Bitmap */
//uint32_t free_page_bitmap_table[SIZE] = {0u};

/* Nombre de page alloué*/

/**
 * @brief Marque la page allouée
 * 
 * Lorsque la page a été choisie, cette fonction permet de la marquer allouée
 * 
 * @param addr Adresse de la page à allouer
 */
void setPage(uint32_t addr) {

    //free_page_bitmap_table[0] = free_page_bitmap_table[0] | (1 << addr);
}

/**
 * @brief Désalloue la page
 * 
 * Libère la page allouée.
 * 
 * @param addr Adresse de la page à libérer
 */
void clearPage(uint32_t addr) {

}

/**
 * @brief Fourni la première page libre de la mémoire physique tout en l'allouant
 * 
 * @return uint32_t Adresse de la page sélectionnée
 */
uint32_t findfreePage() {
    uint32_t adresse= 0x0;

    return adresse;
}

/**
 * @brief Initialise le gestionnaire de mémoire physique
 * 
 */
void init_mem() {

}

/**
 * @brief Affiche l'état de la mémoire physique
 * 
 */
void print_mem() {
    
}