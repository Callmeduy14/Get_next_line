/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 09:07:50 by yyudi             #+#    #+#             */
/*   Updated: 2025/09/27 13:04:59 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_and_join(int fd, char **saved_buffer, char *read_buffer)
{
	int		bytes_read;
	char	*joined_content;
	char	*tmp;

	bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (-1);
	read_buffer[bytes_read] = '\0';
	tmp = *saved_buffer;
	joined_content = ft_strjoin(*saved_buffer, read_buffer);
	if (!joined_content)
		return (-2);
	free(tmp);
	*saved_buffer = joined_content;
	return (bytes_read);
}

char	*append_file_data(int fd, char *saved_buffer)
{
	char	*read_buffer;
	int		bytes_read;

	if (!saved_buffer)
	{
		saved_buffer = ft_strdup("");
		if (!saved_buffer)
			return (NULL);
	}
	read_buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!read_buffer)
		return (free(saved_buffer), NULL);
	bytes_read = 1;
	while (!ft_strchr(saved_buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read_and_join(fd, &saved_buffer, read_buffer);
		if (bytes_read == -1)
			return (free(read_buffer), free(saved_buffer), NULL);
		if (bytes_read == -2)
		{
			free(read_buffer);
			return (NULL);
		}
	}
	return (free(read_buffer),saved_buffer);
}

char	*extract_current_line(char *saved_buffer)
{
	size_t	index;

	if (!saved_buffer || !*saved_buffer)
		return (NULL);
	index = 0;
	while (saved_buffer[index] && saved_buffer[index] != '\n')
		index++;
	if (saved_buffer[index] == '\n')
		return (ft_substr(saved_buffer, 0, index + 1));
	return (ft_strdup(saved_buffer));
}

char	*remove_returned_line(char *saved_buffer)
{
	size_t	index;
	char	*remaining_content;

	if (!saved_buffer)
		return (NULL);
	index = 0;
	while (saved_buffer[index] && saved_buffer[index] != '\n')
		index++;
	if (!saved_buffer[index])
		return (free(saved_buffer), NULL);
	remaining_content = ft_substr(saved_buffer,
			index + 1, ft_strlen(saved_buffer) - index - 1);
	free(saved_buffer);
	return (remaining_content);
}

char	*get_next_line(int fd)
{
	static char	*saved_buffer;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (saved_buffer)
		{
			free(saved_buffer);
			saved_buffer = NULL;
		}
		return (NULL);
	}
	saved_buffer = append_file_data(fd, saved_buffer);
	if (!saved_buffer)
		return (NULL);
	next_line = extract_current_line(saved_buffer);
	saved_buffer = remove_returned_line(saved_buffer);
	if (!next_line || !*next_line)
	{
		free(next_line);
		if (saved_buffer)
		{
			free(saved_buffer);
			saved_buffer = NULL;
		}
		return (NULL);
	}
	return (next_line);
}

#include <stdio.h>
#include <fcntl.h>
int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	fd = 0;
	if (argc > 1)
		fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		write(1, line, ft_strlen(line));
		free(line);
	}
	if (fd > 2)
		close(fd);
	return (0);
}
