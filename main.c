#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

// Pilih salah satu: GET_NEXT_LINE_BONUS untuk versi bonus
#ifdef GET_NEXT_LINE_BONUS
# include "get_next_line_bonus.h"
#else
# include "get_next_line.h"
#endif

int main(int argc, char **argv)
{
    int fd;
    char *line;
    int line_num = 1;

    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%3d: %s", line_num++, line);
        free(line);
    }
    close(fd);
    return 0;
} 