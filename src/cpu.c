#include <stdio.h>

struct cpu {
    char name[5];
    unsigned long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
};

int cpu_read(struct cpu *c) {
    FILE *f = fopen("/proc/stat", "r");
    if (!f) {
        perror("fopen");
        return -1;
    }

    char line[256];

    // leer primera línea
    if (fgets(line, sizeof(line), f)) {

        sscanf(line, "%s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu",
               c->name,
               &c->user,
               &c->nice,
               &c->system,
               &c->idle,
               &c->iowait,
               &c->irq,
               &c->softirq,
               &c->steal,
               &c->guest,
               &c->guest_nice);
    }

    fclose(f);
    return 0;
}