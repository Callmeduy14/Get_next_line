/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:23:08 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/22 12:28:00 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_fd_list	*get_fd_node(t_fd_list **head, int fd)
{
	t_fd_list	*current;
	t_fd_list	*new_node;

	current = *head;
	while (current != NULL)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	new_node = malloc(sizeof(t_fd_list));
	if (new_node == NULL)
		return (NULL);
	new_node->fd = fd;
	new_node->stash = NULL;
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

static void	clean_fd_node(t_fd_list **head, int fd)
{
	t_fd_list	*current;
	t_fd_list	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->stash);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static char	*extract_line(char **stash)
{
	char	*line;
	char	*newline_pos;
	char	*remainder;
	size_t	line_len;

	if (*stash == NULL || **stash == '\0')
		return (NULL);
	newline_pos = ft_strchr(*stash, '\n');
	if (newline_pos == NULL)
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
		return (line);
	}
	line_len = newline_pos - *stash + 1;
	line = ft_substr(*stash, 0, line_len);
	if (line == NULL)
		return (NULL);
	remainder = ft_strdup(newline_pos + 1);
	free(*stash);
	*stash = remainder;
	return (line);
}

static int	read_to_stash(int fd, char **stash)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	char	*new_stash;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		new_stash = ft_strjoin(*stash, buffer);
		if (*stash)
			free(*stash);
		if (new_stash == NULL)
			return (0);
		*stash = new_stash;
		if (ft_strchr(*stash, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1 && *stash)
	{
		free(*stash);
		*stash = NULL;
	}
	return (bytes_read != -1);
}

char	*get_next_line(int fd)
{
	static t_fd_list	*head = NULL;
	t_fd_list			*current;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		if (fd >= 0)
			clean_fd_node(&head, fd);
		return (NULL);
	}
	current = get_fd_node(&head, fd);
	if (current == NULL)
		return (NULL);
	if (!read_to_stash(fd, &current->stash) && !current->stash)
	{
		clean_fd_node(&head, fd);
		return (NULL);
	}
	line = extract_line(&current->stash);
	if (line == NULL || current->stash == NULL)
		clean_fd_node(&head, fd);
	return (line);
}
