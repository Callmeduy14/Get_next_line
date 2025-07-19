/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:17:52 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/19 20:16:25 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Fungsi untuk menghitung panjang string
*/
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

/*
** Fungsi untuk mencari karakter dalam string
*/
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

/*
** Fungsi untuk menggabungkan dua string
*/
char	*ft_strjoin(char *s1, const char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
	{
		result = ft_strdup(s1);
		free(s1);
		return (result);
	}

	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
	{
		free(s1);
		return (NULL);
	}

	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}

	j = 0;
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}

	result[i + j] = '\0';
	free(s1);
	return (result);
}

/*
** Fungsi untuk mengambil substring
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;

	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);

	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

/*
** Fungsi untuk menduplikasi string
*/
char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	i;
	size_t	len;

	if (!s1)
		return (NULL);

	len = ft_strlen(s1);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);

	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
