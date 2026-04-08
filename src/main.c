#include <stdio.h>
#include <unistd.h>
#include "../include/cpu.h"
#include <string.h>

#define MAX_CPUS 16

int main(void) {
    struct cpu prev[MAX_CPUS];
    struct cpu curr[MAX_CPUS];

    int n = cpu_read(prev, MAX_CPUS);
    cpu_read(prev,MAX_CPUS);
    while (1) {        
        sleep(1);
        cpu_read(curr,MAX_CPUS);

        printf("\033[H\033[2J\033[3J");

        for (int i = 0; i < n; i++) {
            unsigned long prev_total = get_total(&prev[i]);
            unsigned long curr_total = get_total(&curr[i]);

            unsigned long delta_total = curr_total - prev_total;
            unsigned long delta_idle = curr[i].idle - prev[i].idle;

            float usage = 0.0;
            if (delta_total > 0) {
                usage = 100.0 * (delta_total - delta_idle) / delta_total;
            }

            printf("%s: %.1f%%\n", curr[i].name, usage);
            

        }
        memcpy(prev, curr, sizeof(struct cpu) * n);
        
    }
}