/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:07:17 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/22 13:32:25 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*gnl_free(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

char	*ft_get_line(int fd, char *line)
{
	char	*buffer;
	ssize_t	read_bytes;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (gnl_free(&line));
	read_bytes = 1;
	while (!ft_strchr(line, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			gnl_free(&buffer);
			return (gnl_free(&line));
		}
		buffer[read_bytes] = '\0';
		line = ft_strjoin(line, buffer);
		if (!line)
		{
			gnl_free(&buffer);
			return (NULL);
		}
	}
	gnl_free(&buffer);
	return (line);
}

char	*new_line(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
		return (gnl_free(&line));
	str = (char *)malloc(ft_strlen(line) - i + 1);
	if (!str)
		return (gnl_free(&line));
	i++;
	j = 0;
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	gnl_free(&line);
	return (str);
}

char	*ft_get_next_line(char *line)
{
	int		i;
	char	*str;

	if (!line || !*line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	str = malloc(i + 1 + (line[i] == '\n'));
	if (!str)
		return (NULL);
	i = -1;
	while (line[++i] && line[i] != '\n')
		str[i] = line[i];
	if (line[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_get_line(fd, line);
	if (!line)
		return (NULL);
	next_line = ft_get_next_line(line);
	if (!next_line)
	{
		gnl_free(&line);
		return (NULL);
	}
	line = new_line(line);
	return (next_line);
}
