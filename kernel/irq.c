#include <inttypes.h>
#include <n7OS/irq.h>


void init_irq_entry(int irq_num, uint32_t addr) {
    // Récupération de l'entrée actuelle dans idt (table des irq)
    idt_entry_t* entry = (idt_entry_t *)&idt[irq_num];

    // Initialisation des valeurs
    entry->offset_inf = addr & 0xFFFF;
    entry->sel_segment = KERNEL_CS;
    entry->type_attr = PRESENT | DPL_HIGH | INTERUPT_GATE | INT_GATE32;
    entry->zero = 0x0;
	entry->offset_sup = addr >> 16;
}
