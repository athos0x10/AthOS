#include <n7OS/mem.h>

/* Mise en place de l'utilisation Bitmap */

/* Bitmap */
uint32_t free_page_bitmap_table[BITMAP_SIZE] = {0u};

/**
 * @brief Marque la page allouée
 * 
 * Lorsque la page a été choisie, cette fonction permet de la marquer allouée
 * 
 * @param addr Adresse de la page à allouer
 */
void setPage(uint32_t addr) {
    // Récupère le numéro de page global
    uint32_t num_page = addr / PAGE_SIZE;

    // Trouve dans quel entier se trouve ce bit
    uint32_t addr_index = num_page / 32u;

    // Trouve la position du bit (0 à 31) au sein de cet entier
    uint32_t bit_index = addr_index % 32u;

    // Marque la page comme allouée (mise à 1)
    free_page_bitmap_table[addr_index] |=  (1u << bit_index);
}

/**
 * @brief Désalloue la page
 * 
 * Libère la page allouée.
 * 
 * @param addr Adresse de la page à libérer
 */
void clearPage(uint32_t addr) {
    // Récupère le numéro de page global
    uint32_t num_page = addr / PAGE_SIZE;

    // Trouve dans quel entier se trouve ce bit
    uint32_t addr_index = num_page / 32u;

    // Trouve la position du bit (0 à 31) au sein de cet entier
    uint32_t bit_index = addr_index % 32u;

    // Libère la page comme allouée (mise à 0)
    free_page_bitmap_table[addr_index] &=  ~(1u << bit_index);
}

/**
 * @brief Fourni la première page libre de la mémoire physique tout en l'allouant
 * 
 * @return uint32_t Adresse de la page sélectionnée
 */
uint32_t findfreePage() {
    uint32_t adresse = 0xFFFFFFFF;
    // Parcours sur le bitmap
    for (uint32_t i = 0u; i < BITMAP_SIZE; i++) {

        //On regarde si le bloc à une page libre
        if (free_page_bitmap_table[i] != 0xFFFFFFFF) {

            // Parcours sur les bits pour trouver la première page libre
            for (uint32_t j = 0u; j < 32u; j++) {
                // Regarde si la page du bit j est libre
                if (!(free_page_bitmap_table[i] & (1u << j))) {
                    //Calcul de l'adresse globale associée
                    adresse = (i * 32u + j)  * PAGE_SIZE;
                    return adresse;
                }
            }
        }
    }
    // Mémoire pleine
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