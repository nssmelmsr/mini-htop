#include <stdio.h>
#include "../include/cpu.h"
#include <string.h>


int cpu_read(struct cpu *cpus, int max_cpus) {
    FILE *f = fopen("/proc/stat", "r");
    if (!f) {
        perror("fopen");
        return -1;
    }

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), f) && count < max_cpus) {
        printf("\033[H\033[2J\033[3J"); //clear terminal

        
        if (strncmp(line, "cpu", 3) != 0) // lines that start with cpu only
            break;

        sscanf(line, "%s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu",
               cpus[count].name,
               &cpus[count].user,
               &cpus[count].nice,
               &cpus[count].system,
               &cpus[count].idle,
               &cpus[count].iowait,
               &cpus[count].irq,
               &cpus[count].softirq,
               &cpus[count].steal,
               &cpus[count].guest,
               &cpus[count].guest_nice);

        count++;
    }

    fclose(f);
    return count; // CPU Read
}