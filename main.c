/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Your Name <your.email@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by Your Name         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by Your Name        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>  // For printf function

/**
 * Main function to test get_next_line
 * Demonstrates how to use the get_next_line function
 */
int	main(void)
{
	int		fd;         // File descriptor for the test file
	char	*line;      // Will store each line read
	int		line_count; // Counter for line numbers

	// Open the test file for reading
	// O_RDONLY means read-only mode
	fd = open("test.txt", O_RDONLY);
	
	// Check if file opened successfully
	if (fd == -1)
	{
		printf("Error: Could not open test.txt\n");
		return (1);
	}

	printf("=== Testing get_next_line function ===\n\n");
	
	line_count = 1;
	
	// Read lines from file one by one
	// get_next_line returns NULL when it reaches end of file
	while ((line = get_next_line(fd)) != NULL)
	{
		// Print line number and the line content
		printf("Line %d: %s", line_count, line);
		line_count++;
		
		// Free the memory allocated for the line
		// This is important to prevent memory leaks
		free(line);
	}

	// Close the file descriptor
	close(fd);
	
	printf("\n=== End of file reached ===\n");
	printf("Total lines read: %d\n", line_count - 1);
	
	return (0);
} 