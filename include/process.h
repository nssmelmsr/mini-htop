#ifndef PROC_H
#define PROC_H

struct process {
    char name[256];
    unsigned int pid;
    unsigned long utime, stime, total_time;
};

unsigned long get_process(struct process *proc, int process_showing);

#endif