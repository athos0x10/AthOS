#include <n7OS/paging.h>
#include <stddef.h> // nécessaire pour NULL
#include <n7OS/mem.h>
#include <n7OS/kheap.h>
#include <n7OS/processor_structs.h>

//Le répertoire de page
PageDirectory page_dir;

void initialise_paging() {
    // Initialisation de la mémoire physique
    init_mem();

    // Allocation d'une zone mémoire pour le repertoire de pages
    page_dir = (PageDirectory) kmalloc_a(PAGE_SIZE);

    // Initialisation du répertoire de page
    // On alloue de la mémoire que quand c'est demandé
    for (uint16_t i = 0u; i < ENTRIES_PER_DIR; i++) {
        page_dir[i].value = 0u;
    }

    // Mapping d'une table de page (On-Demand paging)
    for (uint32_t i = 0u; i < PT_COVERAGE; i += PAGE_SIZE) { 
        alloc_page_entry(i, 1, 1); 
    }

    // Chargement du repertoire dans le registre CR3
    __asm__ __volatile__("mov %0, %%cr3" :: "r"(page_dir));

    // Lancement de la pagination (Bit 31 de CR0)
    start_paging();

    setup_base((uint32_t)page_dir);
}

void start_paging() {
    uint32_t cr0;
    __asm__ __volatile__("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000; // Positionne le bit PG à 1
    __asm__ __volatile__("mov %0, %%cr0" :: "r"(cr0));
}

void allocate_new_table(uint32_t repertory_idx) {
    // Allocation mémoire de la nouvelle table (4096 octets)
    uint32_t new_table_addr = (uint32_t) kmalloc_a(PAGE_SIZE);

    // Modification du répertoire
    page_dir[repertory_idx].page_directory.P = PRESENT;
    page_dir[repertory_idx].page_directory.U = 1;
    page_dir[repertory_idx].page_directory.W = ECRITURE;

    // On insère l'adresse physique de la table (décalée de 12 bits)
    page_dir[repertory_idx].page_directory.ADDR = (new_table_addr >> 12);
}

PageTable alloc_page_entry(uint32_t address, int is_writeable, int is_kernel) {
    // Permet d'avoir un accès direct aux index via l'union
    addr_virtu_t addr_virtu;
    addr_virtu.value = address;

    uint32_t rep_idx = addr_virtu.struct_value.IND_REPER;
    uint32_t tab_idx = addr_virtu.struct_value.IND_TABLE;

    // Vérification de la table dans le répertoire
    if (page_dir[rep_idx].page_directory.P == 0) {
        // Allocation et liaison de la nouvelle table
        allocate_new_table(rep_idx);
    }

    // Récupération de la table correspondante
    PDE pde = page_dir[rep_idx];
    PageTable pt = (PageTable)(pde.page_directory.ADDR << 12);
    PTE *pte = &pt[tab_idx];

    // Modification de la table 
    pte->page_entry.P = PRESENT;
    pte->page_entry.U = !is_kernel;
    pte->page_entry.W = is_writeable;
    pte->page_entry.PAGE = findfreePage() >> 12;
    
    return pt;   
}
