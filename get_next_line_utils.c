/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 09:13:20 by yyudi             #+#    #+#             */
/*   Updated: 2025/09/26 18:03:28 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	length;

	if (!str)
		return (0);
	length = 0;
	while (str[length])
		length++;
	return (length);
}

char	*ft_strchr(const char *str, int search_char)
{
	while (*str)
	{
		if (*str == (char)search_char)
			return ((char *)str);
		str++;
	}
	if ((char)search_char == '\0')
		return ((char *)str);
	return (NULL);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	sl;
	size_t	i;
	char	*out;

	if (!s)
		return (NULL);
	sl = ft_strlen(s);
	if (start >= sl)
		return (ft_strdup(""));
	if (len > sl - start)
		len = sl - start;
	out = (char *)malloc(len + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < len)
	{
		out[i] = s[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

char	*ft_strjoin(const char *first, const char *second)
{
	char	*joined;
	size_t	i;
	size_t	j;

	if (!first || !second)
		return (NULL);
	joined = (char *)malloc(ft_strlen(first) + ft_strlen(second) + 1);
	if (!joined)
		return (NULL);
	i = 0;
	while (first[i])
	{
		joined[i] = first[i];
		i++;
	}
	j = 0;
	while (second[j])
		joined[i++] = second[j++];
	joined[i] = '\0';
	return (joined);
}

char	*ft_strdup(const char *source_str)
{
	char	*copy;
	size_t	i;

	if (!source_str)
		return (ft_strdup(""));
	copy = (char *)malloc(ft_strlen(source_str) + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < ft_strlen(source_str))
	{
		copy[i] = source_str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
