/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Your Name <your.email@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by Your Name         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by Your Name        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>  // For printf function

/**
 * Main function to test get_next_line BONUS version
 * Demonstrates multiple file descriptor support
 */
int	main(void)
{
	int		fd1;        // File descriptor for first file
	int		fd2;        // File descriptor for second file
	char	*line1;     // Will store lines from first file
	char	*line2;     // Will store lines from second file
	int		line_count; // Counter for line numbers

	// Open the first test file for reading
	fd1 = open("test.txt", O_RDONLY);
	if (fd1 == -1)
	{
		printf("Error: Could not open test.txt\n");
		return (1);
	}

	// Open the second test file for reading
	fd2 = open("test2.txt", O_RDONLY);
	if (fd2 == -1)
	{
		printf("Error: Could not open test2.txt\n");
		close(fd1);
		return (1);
	}

	printf("=== Testing get_next_line BONUS (Multiple File Descriptors) ===\n\n");
	
	line_count = 1;
	
	// Read lines from both files alternately
	// This demonstrates that the function can handle multiple file descriptors
	while (1)
	{
		// Read from first file
		line1 = get_next_line(fd1);
		if (line1)
		{
			printf("File 1, Line %d: %s", line_count, line1);
			free(line1);
		}
		
		// Read from second file
		line2 = get_next_line(fd2);
		if (line2)
		{
			printf("File 2, Line %d: %s", line_count, line2);
			free(line2);
		}
		
		// If both files are finished, break
		if (!line1 && !line2)
			break;
		
		line_count++;
	}

	// Close the file descriptors
	close(fd1);
	close(fd2);
	
	printf("\n=== End of files reached ===\n");
	printf("Total iterations: %d\n", line_count - 1);
	
	return (0);
} 