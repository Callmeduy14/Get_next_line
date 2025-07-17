#include "get_next_line_bonus.h"

// Structure to hold stash for each file descriptor
typedef struct s_fd_list
{
	int					fd;
	char				*stash;
	struct s_fd_list	*next;
}	t_fd_list;

// Helper function to find or create fd node in the list
static t_fd_list	*get_fd_node(t_fd_list **fd_list, int fd)
{
	t_fd_list	*current;
	t_fd_list	*new_node;

	current = *fd_list;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	// Create new node if not found
	new_node = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->stash = NULL;
	new_node->next = *fd_list;
	*fd_list = new_node;
	return (new_node);
}

// Helper function to clean up and remove fd node when done
static void	clean_fd_node(t_fd_list **fd_list, int fd)
{
	t_fd_list	*current;
	t_fd_list	*prev;

	current = *fd_list;
	prev = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				*fd_list = current->next;
			free(current->stash);
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

// Helper function to read from fd and append to stash
static char	*read_and_append(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;
	char	*temp;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = stash;
		stash = ft_strjoin(stash, buffer);
		free(temp);
		if (!stash)
			break;
	}
	free(buffer);
	return (stash);
}

// Helper function to extract a line from stash
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

// Helper function to update stash by removing the returned line
static char	*update_stash(char *stash)
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
	new_stash = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
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

// Main function to get next line from any fd
char	*get_next_line(int fd)
{
	static t_fd_list	*fd_list = NULL;
	t_fd_list			*current_fd;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	current_fd = get_fd_node(&fd_list, fd);
	if (!current_fd)
		return (NULL);
	current_fd->stash = read_and_append(fd, current_fd->stash);
	if (!current_fd->stash)
	{
		clean_fd_node(&fd_list, fd);
		return (NULL);
	}
	line = extract_line(current_fd->stash);
	current_fd->stash = update_stash(current_fd->stash);
	if (!current_fd->stash)
		clean_fd_node(&fd_list, fd);
	return (line);
}