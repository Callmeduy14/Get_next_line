/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Your Name <your.email@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by Your Name         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by Your Name        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// Include necessary libraries
# include <stdlib.h>  // For malloc, free, NULL
# include <unistd.h>  // For read function
# include <fcntl.h>   // For file operations

// Define buffer size for reading
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// Function prototypes
char	*get_next_line(int fd);           // Main function to get next line
char	*ft_read_and_join(int fd, char *stash);  // Read from fd and join with stash
char	*ft_extract_line(char *stash);    // Extract one line from stash
char	*ft_clean_stash(char *stash);     // Remove extracted line from stash
char	*ft_strjoin(char *s1, char *s2);  // Join two strings
char	*ft_strchr(char *s, int c);       // Find character in string
size_t	ft_strlen(char *s);              // Get string length
char	*ft_strdup(char *s);              // Duplicate string

#endif 