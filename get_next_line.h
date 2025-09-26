/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 09:09:26 by yyudi             #+#    #+#             */
/*   Updated: 2025/09/26 14:07:17 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int search_char);
char	*ft_strdup(const char *source_str);
char	*ft_strjoin(const char *first, const char *second);
char	*ft_substr(const char *source_str,
			unsigned int start_index, size_t len);

#endif