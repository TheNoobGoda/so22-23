#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int pipe1()
{
    int fd;

    // FIFO file path
    char *myfifo = "./myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(myfifo, 0666);
    char *arr1, *arr2;
    for (int i = 0; i < 3; i++)
    {
        // Open FIFO for write only
        fd = open(myfifo, O_WRONLY);
        // Take an input arr2ing from user.
        // 80 is maximum length
        arr2 = "Test";
        // Write the input arr2ing on FIFO
        // and close it
        write(fd, arr2, strlen(arr2) + 1);
        close(fd);

        // Open FIFO for Read only
        fd = open(myfifo, O_RDONLY);
        // Read from FIFO
        read(fd, arr1, sizeof(arr1));

        // Print the read message
        printf("User2: %s\n", arr1);
        close(fd);
    }
    return 0;
}
int pipe2()
{
    int fd1;

    // FIFO file path
    char *myfifo = "./myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>,<permission>)
    mkfifo(myfifo, 0666);

    char *str1, *str2;
    for (int i = 0; i < 3; i++)
    {
        // First open in read only and read
        fd1 = open(myfifo, O_RDONLY);
        read(fd1, str1, 80);

        // Print the read string and close
        printf("User1: %s\n", str1);
        close(fd1);

        // Now open in write mode and write
        // string taken from user.
        fd1 = open(myfifo, O_WRONLY);
        str2 = "Test2";
        write(fd1, str2, strlen(str2) + 1);
        close(fd1);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    // Confirm exactly three arguments are present
    if (argc != 4)
    {
        printf("usage: tokenring numberProcesses probability time\n");
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    // int p = atoi(argv[2]);
    // int t = atoi(argv[3]);
    for (int i = 0; i < n; i++)
    {
    pid_t pid = getpid();
    int initial = pid;
    printf("Process id: %d\n", pid);
    printf("Initial: %d\n", initial);
    fork();
    pid = getpid();
    int now = pid;
    printf("Process id: %d\n", pid);
    printf("Now: %d\n", now);
    for (int i = 0; i < n; i++)
    {
        if (pid == initial) // Child
        {
            printf("Entrou no 1o\n");
            pipe1();
        }
        else // Parent
        {
            printf("Entrou no 2o\n");
            pipe2();
        }
    }
}