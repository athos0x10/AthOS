#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <n7OS/console.h>
#include <n7OS/paging.h>
#include <n7OS/kheap.h>
#include <n7OS/mem.h>
#include <../include/debug.h>
#include <n7OS/irq.h>
extern void handler_IT50(void);

void kernel_start(void)
{
    initialise_paging();
    init_console();

    // lancement des interruptions
    sti();

    init_irq_entry(50,(uint32_t) handler_IT50);
    /** 
    // test de la pagination
    alloc_page_entry(0xA0000000,1,0); 
    uint32_t *ptr = (uint32_t *) 0xA0000000;
    (*ptr)++;
    */

    // test de l'interruption 50
    __asm__ __volatile__("int $50"::);

    // on ne doit jamais sortir de kernel_start
    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}
