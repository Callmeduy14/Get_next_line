/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:54:45 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/30 10:58:16 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

static char	*ft_read(int fd, char *buffer, char *line, int *b_read)
{
	char	*temp;

	*b_read = 1;
	while (!ft_strchr(buffer, '\n') && *b_read > 0)
	{
		*b_read = read(fd, buffer, BUFFER_SIZE);
		if (*b_read == -1)
			return (free(line), NULL);
		if (*b_read > 0)
		{
			buffer[*b_read] = '\0';
			temp = ft_strjoin(line, buffer);
			if (!temp)
				return (free(line), NULL);
			free(line);
			line = temp;
		}
	}
	return (line);
}

static char	*extract_line(char *line)
{
	size_t	i;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		return (ft_substr(line, 0, i + 1));
	return (ft_strdup(line));
}

static void	buffer_clean(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		i++;
		while (buffer[i])
			buffer[j++] = buffer[i++];
	}
	buffer[j] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*temp;
	int			b_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		buffer[0] = '\0';
		return (NULL);
	}
	line = ft_strdup(buffer);
	if (!line)
		return (NULL);
	line = ft_read(fd, buffer, line, &b_read);
	if (!line)
		return (NULL);
	if (b_read == 0 && *line == '\0')
	{
		free(line);
		return (NULL);
	}
	temp = extract_line(line);
	buffer_clean(buffer);
	free(line);
	return (temp);
}

// #include <fcntl.h>
// #include <stdio.h>

// int main(int argc, char **argv)
// {
// 	if (argc != 2)
// 	{
// 		fprintf(stderr, "Usage: %s test_file.txt \n", argv[0]);
// 		return 1;
// 	 }

// 	int fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return 1;
// 	}

// 	char *line;
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return 0;
// }
