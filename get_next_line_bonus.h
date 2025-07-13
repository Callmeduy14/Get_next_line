/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Your Name <your.email@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by Your Name         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by Your Name        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

// Include necessary libraries
# include <stdlib.h>  // For malloc, free, NULL
# include <unistd.h>  // For read function
# include <fcntl.h>   // For file operations

// Define buffer size for reading
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// Define maximum number of file descriptors (bonus requirement)
# define MAX_FD 1024

// Structure to store stash for each file descriptor
typedef struct s_stash
{
	int		fd;          // File descriptor
	char	*content;    // Stash content for this fd
}	t_stash;

// Function prototypes for bonus version
char	*get_next_line(int fd);                    // Main function (bonus version)
char	*ft_read_and_join_bonus(int fd, char *stash);  // Read and join for bonus
char	*ft_extract_line_bonus(char *stash);       // Extract line (bonus version)
char	*ft_clean_stash_bonus(char *stash);        // Clean stash (bonus version)
char	*ft_strjoin_bonus(char *s1, char *s2);     // Join strings (bonus version)
char	*ft_strchr_bonus(char *s, int c);          // Find character (bonus version)
size_t	ft_strlen_bonus(char *s);                 // String length (bonus version)
char	*ft_strdup_bonus(char *s);                 // String duplicate (bonus version)
t_stash	*ft_find_stash(t_stash **stash_list, int fd);  // Find stash for specific fd
void	ft_cleanup_stash(t_stash **stash_list, int fd); // Cleanup specific stash

#endif 