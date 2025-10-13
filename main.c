#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		line_count;

	if (BUFFER_SIZE <= 0)
		return (0);
	fd = 0;
	if (argc > 1)
		fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	line_count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		write(1, line, ft_strlen(line));
		free(line);
		line_count++;
		if (line_count == 3) // berhenti setelah 3 baris
			break;
	}
	if (fd > 2)
		close(fd);
	return (0);
}