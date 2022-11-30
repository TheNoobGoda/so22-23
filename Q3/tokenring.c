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
    float p = strtof(argv[2], NULL) * 100;
    int t = strtol(argv[3], NULL, 10);
    int n = atoi(argv[1]);

    pid_t pid;
    /*
    char name1[13];
    char name2[13];

    sprintf(name1,"pipe%dto%d",1,2);
    sprintf(name2,"pipe%dto%d",2,1);

    mkfifo(name1,0666);
    mkfifo(name2,0666);
    int token = 0;
    srand(time(0));
    pid = fork();
    if (pid==0){
        int fd1 = open(name1,O_WRONLY);
        int fd2 = open(name2,O_RDONLY);
        while(read(fd2,(char*)&token,sizeof(token))>0){
            token++;
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
    */
    int proc = 1;
    for (int i = 1; i < n; i++)
    {
        char name[13];
        sprintf(name, "pipe%dto%d", i, i + 1);
        mkfifo(name, 0666);
    }
    char name[13];
    sprintf(name, "pipe%dto%d", n, 1);
    mkfifo(name, 0666);
    int token = 0;
    srand(time(0));
    for (int i = 2; i <= n; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            proc = i;
            break;
        }
    }

    char name1[13];
    char name2[13];

    if (proc == n)
    {
        sprintf(name1, "pipe%dto%d", proc, 1);
        sprintf(name2, "pipe%dto%d", proc - 1, proc);
    }
    else
        sprintf(name1, "pipe%dto%d", proc, proc + 1);
    if (proc == 1)
    {
        sprintf(name2, "pipe%dto%d", n, 1);
    }
    else
    {
        sprintf(name2, "pipe%dto%d", proc - 1, proc);
    }

    fflush(stdout);

    int fd2 = open(name2, O_RDONLY | O_NONBLOCK);
    int fd1 = open(name1, O_WRONLY);


    if (proc == 1)
        write(fd1, (char *)&token, sizeof(token));
    while (1)
    {
        int bytes = 0;
        while (bytes <=0){
            bytes = read(fd2, (char *)&token, sizeof(token));
        }
        token++;
        int num = rand() % 100;
        if (num <= p)
        {
            printf("[%d] lock on token (val = %d)\n", getpid(), token);
            sleep(t);
            printf("[%d] unlock on token\n", getpid());
            fflush(stdout);
        }

        write(fd1, (char *)&token, sizeof(token));
    }

    return 0;
}
