#include <stdio.h>
#include <unistd.h>
#include "../include/cpu.h"
#include <string.h>

#define MAX_CPUS 16

int main(void) {
    struct cpu cpus[MAX_CPUS];

    while (1) {
        int n = cpu_read(cpus, MAX_CPUS);

        for (int i = 0; i < n; i++) {
            printf("%s idle: %lu\n", cpus[i].name, cpus[i].idle);
        }

        printf("\n");
        sleep(1);
    }
}