#ifndef CPU_H
#define CPU_H

struct cpu {
    char name[5];
    unsigned long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
};

unsigned int cpu_read(struct cpu *cpus, int max_cpus);

unsigned long get_total(struct cpu *c);

#endif