#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // Confirm exactly three arguments are present
    if (argc != 4)
    {
        printf("usage: tokenring numberProcesses probability time\n");
        return EXIT_FAILURE;
    }
    float p = strtof(argv[2], NULL)*100;
    int t = strtol(argv[3], NULL, 10);
    
    pid_t pid;
    char name1[13];
    char name2[13];

    sprintf(name1,"pipe%dto%d",1,2);
    sprintf(name2,"pipe%dto%d",2,1);

    mkfifo(name1,0666);
    mkfifo(name2,0666);
    int token = 0;
    pid = fork();
    if (pid==0){
        int fd1 = open(name1,O_WRONLY);
        int fd2 = open(name2,O_RDONLY);
        while(read(fd2,(char*)&token,sizeof(token))>0){
            token++;
            srand(time(0));
            int num = rand()%100;
            if (num <= p){
                printf("[%d] lock on token (val = %d)\n",getpid(),token);
                sleep(t);
                printf("[%d] unlock on token\n",getpid());
                fflush(stdout);
            }
            
            write(fd1,(char*)&token,sizeof(token));
        }

    }else {
        int fd1 = open(name1,O_RDONLY);
        int fd2 = open(name2,O_WRONLY);
        write(fd2,(char*)&token,sizeof(token));
        while(read(fd1,(char*)&token,sizeof(token))>0){
            token++;
            srand(time(0));
            int num = rand()%100;
            if (num <= p){
                printf("[%d] lock on token (val = %d)\n",getpid(),token);
                sleep(t);
                printf("[%d] unlock on token\n",getpid());
                fflush(stdout);
            }
            
            write(fd2,(char*)&token,sizeof(token));
        }
    }
    return 0;
}