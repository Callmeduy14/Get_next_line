/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:14:37 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/19 20:10:05 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Di header file (GET_NEXT_LINE_H) */
// Tambahkan pengecekan double inclusion
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>  // Untuk malloc, free
# include <unistd.h>  // Untuk read
# include <limits.h>  // Untuk OPEN_MAX

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42  // Ukuran default buffer
# endif

/* Prototipe fungsi utama */
char	*get_next_line(int fd);

/* Prototipe fungsi utilitas - ubah s1 menjadi char* untuk strjoin */
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, const char *s2);  // Diubah parameter pertama
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);

#endif
