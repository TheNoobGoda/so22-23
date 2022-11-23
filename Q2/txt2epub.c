#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
    if (argc <= 1 ){
        printf("bad usage\n");
        return 0;
    }
    pid_t pid;
    char* files[argc+1];
    files[0] = "zip";
    files[1] = "ebooks.zip";

    for (int i =1;i<argc;i++){
        pid =fork();
        char* name = strcat(strncpy(malloc(strlen(argv[i])+5), argv[i], strlen(argv[i])-4), ".epub");
        files[i+1] = name;
        if (pid == 0){
            printf("[pid%d] converting %s\n",getpid(),name);
            execlp("pandoc","pandoc",argv[i],"-o",name, NULL);
        }
        wait(NULL);
    }
    files[argc+1] = NULL;
    execvp("zip",files);
    return 0;
}