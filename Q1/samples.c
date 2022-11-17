#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//Random number generator with parameters
int randomNumberBetween(int lower, int upper)
{
    int num = rand() % (upper + 1);
    return (num);
}

int main(int argc, char *argv[])
{
    // Confirm exactly three arguments are present
    if (argc != 4)
    {
        printf("usage: samples file numberfrags maxfragsize\n");
        return EXIT_FAILURE;
    }
    // Confirm if file can be opened and is readable
    FILE *fd = fopen(argv[1], "r");
    int numberfrags = atoi(argv[2]);
    int maxfragsize = atoi(argv[3]);
    if (fd == NULL)
    {
        printf("Error: cannot open %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    // Get size of text file - includes line breaks
    fseek(fd, 0L, SEEK_END);
    int size = ftell(fd);
    rewind(fd);
    //Limit = Last point at which random string can begin
    int limit = size - maxfragsize;
    //Srand is used to generate true random sequence
    srand(time(0));
    int random;
    char c;
    //Go through 'text' starting from the random number until random+maxfragsize
    for (int i = 0; i < numberfrags; i++)
    {
        random = randomNumberBetween(0, limit);
        for (int j = random; j < random + maxfragsize; j++)
        {
            fseek( fd, j, SEEK_SET );
            c=getc(fd);
            if (c == '\n')
            {
                c=' ';
            }
            printf("%c",c);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
