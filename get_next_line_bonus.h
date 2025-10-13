/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 09:10:46 by yyudi             #+#    #+#             */
/*   Updated: 2025/09/26 14:07:28 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  if defined(OPEN_MAX)
#   define MAX_FD OPEN_MAX
#  else
#   define MAX_FD 1024
#  endif
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int search_char);
char	*ft_strdup(const char *source_str);
char	*ft_strjoin(const char *first, const char *second);
char	*ft_substr(const char *source_str,
			unsigned int start_index, size_t len);

#endif