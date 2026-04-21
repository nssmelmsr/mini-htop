#include <stdio.h>
#include <ctype.h> //is_digit()
#include <dirent.h>//dir management
#include <unistd.h> //para funcion read()
#include <fcntl.h> //para función open()
#include "../include/process.h"

int isnumber(const char *str){
    if (*str == '\0') return 0;
    for (int i = 0; str[i]; i++){
        if (!isdigit((unsigned char)str[i])){
            return 0;
        }
    } 
    return 1;
}


unsigned int read_process(struct process *p, int pid){

    char path[256];
    char line[1024];

    snprintf(path,sizeof(path),"/proc/%d/stat",pid);

    FILE *f = fopen(path,"r");

    if (f == NULL){
        return -1;
    }

    if (!fgets(line,sizeof(line),f)){
        fclose(f);
        return -1;
    }

    fclose(f);

    char *lparen = strchr(line,'(');        // encontrar nombre entre paréntesis
    char *rparen = strrchr(line,')');

    if (!lparen || !rparen){
        return -1;
    }

    p->pid = pid;

    int len = rparen - lparen - 1;      // obtener nombre

    strncpy(p->name,lparen + 1,len);

    p->name[len] = '\0';

    char *rest = rparen + 2;    // después del ") "



    sscanf(rest,        // saltar campos hasta utime y stime

       "%*c " //state

       "%*d %*d %*d %*d %*d "
       "%*u %*u %*u %*u %*u "

       "%lu %lu",

       &p->utime,
       &p->stime
    );


    p->total_time = p->utime + p->stime;

    return 0;
}

unsigned long get_process(struct process *proc, int process_showing){

    DIR *dir = opendir("/proc");

    if (dir == NULL){
        perror("opendir");
        return -1;
    }

    struct dirent *entry;

    int count = 0;


    while ((entry = readdir(dir)) != NULL &&
            count < process_showing){

        if (isnumber(entry->d_name)){

            int pid = atoi(entry->d_name);


            if (read_process(&proc[count],pid) == 0){

                count++;

            }

        }

    }

    closedir(dir);

    return count;
}
