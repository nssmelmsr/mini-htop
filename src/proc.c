#include <stdio.h>
#include <ctype.h> //is_digit()
#include <dirent.h>//dir management
#include <unistd.h> //para funcion read()
#include <fcntl.h> //para función open()


int isnumber(const char *str){      //analiza nombre de archivo si sólo contiene números devuelve 1
    for(int i=0;str[i];i++){
        if (isdigit(str[i])){
            return 1;
        }
    }
    return 0;
}

unsigned long get_process(void){

    DIR *dir = opendir("/proc");
    ssize_t bytes_read;
    

    if (dir == NULL){
    perror("opendir");
    return 1;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL){         //lee mientras hay archivos
        if (isnumber(entry->d_name)){
            char path[256];
            char name[256];
            snprintf(path, sizeof(path), "/proc/%.243s/comm",entry->d_name); //256 - 12 ("/proc//comm") -1 (bit de terminación) esto evita sobreflujo
            int fd = open(path,O_RDONLY);
            if (fd == -1){
				perror("Error openning file");    // perror shows the error code of the syscall
				continue;
			}
            bytes_read = read(fd, name, sizeof(name) -1);//lee el archivo

			if (bytes_read == -1){
				perror("Error reading file");
				close(fd);
				return 1;
			}
            if (bytes_read > 0) {
                name[bytes_read] = '\0';
                printf("%s\t%s",entry->d_name,name);  
            }
            
            close(fd);
        }
    }
    closedir(dir);
    return 0;    
}