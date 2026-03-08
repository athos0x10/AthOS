/**
 * @file paging.h
 * @brief Gestion de la pagination dans le noyau
 */
#ifndef _PAGING_H
#define _PAGING_H

/* Définition de constantes pour simplifier la lecture. */
#define PRESENT 1
#define ECRITURE 1
#define NOYAU 0

#define ENTRIES_PER_TABLE    1024      // Nombre de PTE dans une Page Table
#define ENTRIES_PER_DIR      1024      // Nombre de PDE dans le Page Directory
#define PT_COVERAGE          0x400000  // Mémoire couverte par une table (4 Mo)

#include <inttypes.h>

/* Répertoire de page. */

/**
 * @brief Description d'une ligne du répertoire de page.
 * 
 */
typedef struct {
    uint32_t P :     1; //Présence de la page en mémoire
    uint32_t W :     1; //Page accessible en lecture/écriture
    uint32_t U :     1; // Page utilisateur si U==1, noyau sinon
    uint32_t RSVD :  9; //Réservé
    uint32_t ADDR : 20; // Adresse de la page en mémoire physique
} page_repertory_entry_t;

/**
 * @brief Une entrée dans le répertoire de page peut être manipulé en utilisant
 * la structure page_repertory_entry_t ou directement la valeur.
 */
typedef union {
    page_repertory_entry_t page_directory;
    uint32_t value;
} PDE; // PDE = Page Directory Entry

/* Une table de répertoire de page (PageDirectory) est un tableau. */
typedef PDE * PageDirectory;

/* Table de page. */

/**
 * @brief Description d'une ligne de la table de page
 * 
 */
typedef struct {
    uint32_t P :     1; //Présence de la page en mémoire
    uint32_t W :     1; //Page accessible en lecture/écriture
    uint32_t U :     1; // Page utilisateur si U==1, noyau sinon
    uint32_t RSVD1 : 2; // Réservé
    uint32_t A :     1; // Accessed bit
    uint32_t D :     1; //Dirty bit
    uint32_t RSVD2 : 2; // Réservé
    uint32_t AVAIL : 3;
    uint32_t PAGE : 20; // Adresse de la table page
} page_table_entry_t;

/**
 * @brief Une entrée dans la table de page peut être manipulée en utilisant
 *        la structure page_table_entry_t ou directement la valeur
 */
typedef union {
    page_table_entry_t page_entry;
    uint32_t value;
} PTE; // PTE = Page Table Entry 

/**
 * @brief Une table de page (PageTable) est un tableau de descripteurs de page
 * 
 */
typedef PTE * PageTable;

/* Adresse virtuelle. */

/**
 * @brief Description d'une adresse virtuelle de la mémoire.
 * 
 */
typedef struct {
    uint32_t IND_PAGE  : 12; 
    uint32_t IND_TABLE : 10;
    uint32_t IND_REPER : 10;
} addr_virtu_struct;

typedef union {
    addr_virtu_struct struct_value;
    uint32_t value;
} addr_virtu_t;


/**
 * @brief Cette fonction initialise le répertoire de page, alloue les pages de table du noyau
 *        et active la pagination.
 * 
 */
void initialise_paging();

/**
 * @brief Cette fonction lance la pagination.
 * 
 */
void start_paging();

/**
 * @brief Cette fonction alloue une nouvelle table à l'adresse voulue.
 * @param repertory_idx
 */
void allocate_new_table(uint32_t repertory_idx);

/**
 * @brief Cette fonction alloue une page de la mémoire physique à une adresse de la mémoire virtuelle
 * 
 * @param address       Adresse de la mémoire virtuelle à mapper
 * @param is_writeable  Si is_writeable == 1, la page est accessible en écriture
 * @param is_kernel     Si is_kernel == 1, la page ne peut être accédée que par le noyau
 * @return PageTable    La table de page modifiée
 */
PageTable alloc_page_entry(uint32_t address, int is_writeable, int is_kernel);
#endif