/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Your Name <your.email@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by Your Name         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by Your Name        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Static variable to store remaining data between function calls
// This acts as a "stash" that persists across multiple calls to get_next_line
static char	*stash = NULL;

/**
 * Main function: get_next_line
 * Reads one line at a time from a file descriptor
 * 
 * @param fd: File descriptor to read from
 * @return: Pointer to the line read (without newline), or NULL if error/EOF
 */
char	*get_next_line(int fd)
{
	char		*line;      // Will store the line to return
	char		*temp_stash; // Temporary variable for stash management

	// Input validation: check if fd is valid and BUFFER_SIZE is positive
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	// Read from file descriptor and join with existing stash
	// This function handles the reading process and updates the stash
	stash = ft_read_and_join(fd, stash);
	
	// If stash is NULL after reading, return NULL (EOF or error)
	if (!stash)
		return (NULL);

	// Extract one complete line from the stash
	// This function finds the first newline and returns everything up to it
	line = ft_extract_line(stash);
	
	// Clean the stash by removing the extracted line
	// This keeps only the remaining data for next function call
	temp_stash = stash;
	stash = ft_clean_stash(stash);
	free(temp_stash);

	// Return the extracted line
	return (line);
}

/**
 * Function: ft_read_and_join
 * Reads data from file descriptor and joins it with existing stash
 * 
 * @param fd: File descriptor to read from
 * @param stash: Current stash containing previous data
 * @return: Updated stash with new data joined
 */
char	*ft_read_and_join(int fd, char *stash)
{
	char	*buffer;     // Temporary buffer for reading
	int		bytes_read;  // Number of bytes read from file
	char	*temp;       // Temporary variable for string operations

	// Allocate memory for buffer (size defined by BUFFER_SIZE)
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);

	// Initialize buffer with zeros
	buffer[0] = '\0';

	// Read from file descriptor in a loop until we find a newline or reach EOF
	bytes_read = 1; // Initialize to 1 to enter the loop
	while (bytes_read > 0 && !ft_strchr(stash, '\n'))
	{
		// Read BUFFER_SIZE bytes from file descriptor
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		
		// If read failed, free buffer and return NULL
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		
		// Null-terminate the buffer at the position where we stopped reading
		buffer[bytes_read] = '\0';
		
		// Join the buffer content with existing stash
		temp = stash;
		stash = ft_strjoin(stash, buffer);
		free(temp);
		
		// If strjoin failed, free buffer and return NULL
		if (!stash)
		{
			free(buffer);
			return (NULL);
		}
	}

	// Free the buffer as it's no longer needed
	free(buffer);
	
	// Return the updated stash
	return (stash);
}

/**
 * Function: ft_extract_line
 * Extracts one complete line from the stash (up to newline or end)
 * 
 * @param stash: String containing data with possible newlines
 * @return: New string containing one line (without newline character)
 */
char	*ft_extract_line(char *stash)
{
	int		i;          // Counter for string iteration
	char	*line;      // The line to return

	// If stash is empty, return NULL
	if (!stash || stash[0] == '\0')
		return (NULL);

	i = 0;
	// Find the position of newline character or end of string
	while (stash[i] && stash[i] != '\n')
		i++;

	// Allocate memory for the line (i + 1 for null terminator, +1 if newline found)
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);

	i = 0;
	// Copy characters from stash to line until newline or end
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}

	// If we found a newline, include it in the line
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}

	// Null-terminate the line
	line[i] = '\0';
	
	// Return the extracted line
	return (line);
}

/**
 * Function: ft_clean_stash
 * Removes the extracted line from stash, keeping only remaining data
 * 
 * @param stash: Current stash containing the line to remove
 * @return: New stash with the extracted line removed
 */
char	*ft_clean_stash(char *stash)
{
	int		i;          // Counter for finding newline position
	int		j;          // Counter for copying remaining data
	char	*new_stash; // New stash without the extracted line

	// If stash is empty, return NULL
	if (!stash)
		return (NULL);

	i = 0;
	// Find the position after the newline character
	while (stash[i] && stash[i] != '\n')
		i++;

	// If no newline found, return NULL (no remaining data)
	if (!stash[i])
		return (NULL);

	// Calculate length of remaining data after newline
	i++; // Move past the newline character
	j = 0;
	while (stash[i + j])
		j++;

	// Allocate memory for new stash (remaining data + null terminator)
	new_stash = malloc(sizeof(char) * (j + 1));
	if (!new_stash)
		return (NULL);

	j = 0;
	// Copy remaining data after newline to new stash
	while (stash[i])
	{
		new_stash[j] = stash[i];
		i++;
		j++;
	}

	// Null-terminate the new stash
	new_stash[j] = '\0';
	
	// Return the cleaned stash
	return (new_stash);
}

/**
 * Function: ft_strjoin
 * Joins two strings together, allocating new memory
 * 
 * @param s1: First string (can be NULL)
 * @param s2: Second string (can be NULL)
 * @return: New string containing s1 + s2, or NULL if allocation fails
 */
char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;  // The joined string
	int		i;        // Counter for first string
	int		j;        // Counter for second string

	// Handle NULL strings
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));

	// Calculate total length needed
	i = ft_strlen(s1);
	j = ft_strlen(s2);

	// Allocate memory for joined string
	result = malloc(sizeof(char) * (i + j + 1));
	if (!result)
		return (NULL);

	// Copy first string
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}

	// Copy second string
	j = 0;
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}

	// Null-terminate the result
	result[i + j] = '\0';
	
	// Return the joined string
	return (result);
}

/**
 * Function: ft_strchr
 * Finds the first occurrence of a character in a string
 * 
 * @param s: String to search in
 * @param c: Character to find
 * @return: Pointer to first occurrence of c, or NULL if not found
 */
char	*ft_strchr(char *s, int c)
{
	int	i;  // Counter for string iteration

	// If string is NULL, return NULL
	if (!s)
		return (NULL);

	i = 0;
	// Search for the character in the string
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}

	// Check if we're looking for null terminator
	if ((char)c == '\0')
		return (&s[i]);

	// Character not found
	return (NULL);
}

/**
 * Function: ft_strlen
 * Calculates the length of a string
 * 
 * @param s: String to measure
 * @return: Length of the string (number of characters)
 */
size_t	ft_strlen(char *s)
{
	size_t	len;  // Length counter

	// If string is NULL, return 0
	if (!s)
		return (0);

	len = 0;
	// Count characters until null terminator
	while (s[len])
		len++;

	return (len);
}

/**
 * Function: ft_strdup
 * Duplicates a string, allocating new memory
 * 
 * @param s: String to duplicate
 * @return: New string identical to s, or NULL if allocation fails
 */
char	*ft_strdup(char *s)
{
	char	*dup;  // The duplicated string
	int		i;     // Counter for copying

	// If string is NULL, return NULL
	if (!s)
		return (NULL);

	// Calculate length and allocate memory
	i = ft_strlen(s);
	dup = malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);

	// Copy the string
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}

	// Null-terminate the duplicated string
	dup[i] = '\0';
	
	// Return the duplicated string
	return (dup);
} 