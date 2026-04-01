#include<stdio.h>
#include<dirent.h> //directory management
#include<unistd.h> //para funcion read()
#include<fcntl.h> //para función open()

struct cpu{
    char name[4];
    unsigned long user,nice,system,idle,iowait,irq,softirq,steal, nice, guest_nice;
}
void iscpu(const char *str){    

    while (*str){
        for (int i = 0; i < sizeof(str) ; i++ ){
            if (str[i] == 'c' && str[i+1] == 'p' && str[i+2] == 'u'){{
                
            }
        }
    }
    return 0;
}

int cpu_read(void){
    int fd;
    char buffer[4096]; 		// maximum to read
	ssize_t bytes_read;
    
    

    fd = open("/proc/stat", O_RDONLY); //open file to read only
		if (fd == -1){
    		perror("Error openning file");    // perror shows the error code of the syscall
    		return 1;
    }
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0){    // read whole file
            char *ptr = buffer;
            iscpu(*ptr);    
        
    }
    close(fd); 
}