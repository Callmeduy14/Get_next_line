/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:54:13 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/30 10:47:40 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	size_t	new_start;

	i = 0;
	new_start = 0;
	while (buffer[new_start] && buffer[new_start] != '\n')
		new_start++;
	if (buffer[new_start] == '\n')
	{
		new_start++;
		while (buffer[new_start + i])
		{
			buffer[i] = buffer[new_start + i];
			i++;
		}
	}
	buffer[i] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[MAX_FD][BUFFER_SIZE + 1];
	int			b_read;
	char		*line;
	char		*temp;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, buffer[fd], 0) == -1)
	{
		buffer[fd][0] = '\0';
		return (NULL);
	}
	line = ft_strdup(buffer[fd]);
	if (!line)
		return (NULL);
	line = ft_read(fd, buffer[fd], line, &b_read);
	if (!line || (b_read == 0 && *line == '\0'))
	{
		free(line);
		return (NULL);
	}
	temp = extract_line(line);
	buffer_clean(buffer[fd]);
	free(line);
	return (temp);
}

// #include <fcntl.h>
// #include <stdio.h>

// int main(void)
// {
//     int fd1 = open("file1.txt", O_RDONLY);
//     int fd2 = open("file2.txt", O_RDONLY);
//     char *line1;
//     char *line2;

//     if (fd1 < 0 || fd2 < 0)
//     {
//         perror("File open error");
//         return (1);
//     }

//     printf("Reading from file1.txt and file2.txt alternately:\n\n");

//     while (1)
//     {
//         line1 = get_next_line(fd1);
//         line2 = get_next_line(fd2);

//         if (!line1 && !line2)
//             break;

//         if (line1)
//         {
//             printf("[file1] %s", line1);
//             free(line1);
//         }

//         if (line2)
//         {
//             printf("[file2] %s", line2);
//             free(line2);
//         }
//     }

//     close(fd1);
//     close(fd2);
//     return (0);
// }
