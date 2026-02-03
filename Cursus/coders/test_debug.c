#include "codexion.h"
#include <stdio.h>

int main() {
    t_sim sim = {0};
    sim.number_of_coders = 5;
    sim.time_to_burnout = 500;
    sim.time_to_compile = 150;
    sim.time_to_debug = 100;
    sim.time_to_refactor = 100;
    sim.number_of_compiles_required = 5;
    sim.dongle_cooldown = 20;
    sim.scheduler = FIFO;
    
    if (!init_sim(&sim)) {
        printf("Init failed\n");
        return 1;
    }
    
    printf("Coders initialized:\n");
    for (int i = 0; i < sim.number_of_coders; i++) {
        printf("Coder %d: ldongle=%d, rdongle=%d\n", 
            sim.coders[i].id, 
            sim.coders[i].ldongle->id,
            sim.coders[i].rdongle->id);
    }
    
    printf("\nDongles initialized:\n");
    for (int i = 0; i < sim.number_of_coders; i++) {
        printf("Dongle %d: is_free=%d, queue_len=%d\n",
            sim.dongles[i].id,
            sim.dongles[i].is_free,
            sim.dongles[i].queue->qlength);
    }
    
    destroy_sim(&sim);
    return 0;
}
