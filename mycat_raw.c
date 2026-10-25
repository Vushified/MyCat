#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define Buf_Size 4096
static int copy_fd(int, const char *);

int main(int argc, char *argv[])
{
    int failure = 0;
    int fd = 0;

    if (argc == 1)
    {
        if (copy_fd(0, "stdin") == -1)
        {
            return 1;
        }
    }

    for (int i = 1; i < argc; i++)
    {

        fd = open(argv[i], O_RDONLY, 0);
        if (fd == -1)
        {
            fprintf(stderr, "mycat_raw: %s: %s\n", argv[i], strerror(errno));
            failure++;
            continue;
        }
        // A -1 from copy_fd covers two different failures. A read error on one file shouldn’t stop the others. A write error on stdout will happen for every later file too. we will cover this in next commit
        if (copy_fd(fd, argv[i]) == -1)
        {
            failure++;
        }

        int j;
        j = close(fd);
        if (j == -1)
        {
            fprintf(stderr, "mycat_raw: %s: %s\n", argv[i], strerror(errno));
            failure++;
        }
    }

    return failure > 0 ? 1 : 0;
}

static int copy_fd(int fd, const char *name)
{
    char buff[Buf_Size];
    ssize_t r;
    ssize_t w;

    while (1)
    {
        r = read(fd, buff, Buf_Size);
        if (r == -1)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else
            {
                fprintf(stderr, "mycat_raw: %s: %s\n", name, strerror(errno));
                return -1;
            }
        }
        else if (r == 0)
        {
            return 0;
        }
        ssize_t count = r;
        char *point = buff;
        int retry_flagw = 1;
        while (count > 0)
        {
            w = write(1, point, count);
            if (w == -1)
            {
                // EINTR means there was an interrupt and nothing is written hence retry, it is not fatal error
                if (errno == EINTR)
                {
                    continue;
                }
                else
                {
                    fprintf(stderr, "mycat_raw: stdout: %s\n", strerror(errno));
                    return -1;
                }
            }

            if (w == 0)
            {
                if (retry_flagw == 0)
                {
                    fprintf(stderr, "mycat_raw: stdout: write made no progress\n");
                    return -1;
                }
                else
                {
                    retry_flagw = 0;
                }
            }
            else
            {
                retry_flagw = 1;
            }

            count = count - w;
            point = point + w;
        }
    }
    return 0;
}
