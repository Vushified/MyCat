#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    FILE *f;

    if (argc == 1)
    {
        int k;
        k = getchar();
        while (k != EOF)
        {
            putchar(k);
            k = getchar();
        }
    }
    for (int i = 1; i < argc; i++)
    {
        f = fopen(argv[i], "r");
        if (f == NULL)
        {
            fprintf(stderr, "Error opening file %s: %s\n", argv[i], strerror(errno));
            continue;
        }
        else
        {
            fprintf(stderr, "file open successfull\n");
        }

        int c;
        c = getc(f);
        while (c != EOF)
        {
            putchar(c);
            c = getc(f);
        }

        int j;
        j = fclose(f);
        if (j == EOF)
        {
            fprintf(stderr, "Error closing file %s: %s\n", argv[i], strerror(errno));
        }
        else
        {
            fprintf(stderr, "file close successfull\n");
        }
    }

    return 0;
}
