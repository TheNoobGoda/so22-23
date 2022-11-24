#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    // Confirm exactly three arguments are present
    if (argc != 4)
    {
        printf("usage: tokenring numberProcesses probability time\n");
        return EXIT_FAILURE;
    }
    pid_t pid;
    char* name1 = "./pipe1";
    char* name2 = "./pipe2";

    mkfifo(name1,0666);
    mkfifo(name2,0666);
    int token = 0;
    pid = fork();
    if (pid==0){
        int fd1 = open(name1,O_WRONLY);
        int fd2 = open(name2,O_RDONLY);
        while(read(fd2,(char*)&token,sizeof(token))>0){
            token++;
            printf("%d\n",token);
            fflush(stdout);
            write(fd1,(char*)&token,sizeof(token));
        }

    }else {
        int fd1 = open(name1,O_RDONLY);
        int fd2 = open(name2,O_WRONLY);
        write(fd2,(char*)&token,sizeof(token));
        while(read(fd1,(char*)&token,sizeof(token))>0){
            token++;
            printf("%d\n",token);
            fflush(stdout);
            write(fd2,(char*)&token,sizeof(token));
        }
    }
    return 0;
}