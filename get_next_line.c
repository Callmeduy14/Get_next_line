/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:07:17 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/19 20:15:47 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Deklarasi fungsi helper terlebih dahulu */
static char	*read_to_stash(int fd, char *stash);
static char	*extract_line(char *stash);
static char	*clean_stash(char *stash);

/*
** Fungsi utama get_next_line
*/
char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	// Pengecekan error
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);

	// Baca dari fd dan simpan ke stash
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);

	// Ambil satu baris dari stash
	line = extract_line(stash);

	// Update stash dengan sisa string
	stash = clean_stash(stash);

	return (line);
}

/*
** Fungsi untuk membaca dari fd dan menambahkan ke stash
*/
static char	*read_to_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free(stash);
		return (NULL);
	}

	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			break;
	}
	free(buffer);
	return (stash);
}

/*
** Fungsi untuk mengambil satu baris dari stash
*/
static char	*extract_line(char *stash)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!stash || !stash[i])
		return (NULL);

	while (stash[i] && stash[i] != '\n')
		i++;

	if (stash[i] == '\n')
		i++;

	line = ft_substr(stash, 0, i);
	return (line);
}

/*
** Fungsi untuk membersihkan stash setelah ekstrak baris
*/
static char	*clean_stash(char *stash)
{
	size_t	i;
	size_t	j;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;

	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}

	new_stash = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}

	i++;
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';

	free(stash);
	return (new_stash);
}
