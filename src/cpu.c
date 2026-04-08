#include <stdio.h>
#include "../include/cpu.h"
#include <string.h>

unsigned long get_total(struct cpu *c) {
    return c->user + c->nice + c->system +
           c->idle + c->iowait + c->irq +
           c->softirq + c->steal;
}

unsigned int cpu_read(struct cpu *cpus, int max_cpus) {
    FILE *f = fopen("/proc/stat", "r");
    if (!f) {
        perror("fopen");
        return -1;
    }

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), f) && count < max_cpus) {
        
        if (strncmp(line, "cpu", 3) != 0) // lines that start with cpu only, 0 means its equal
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