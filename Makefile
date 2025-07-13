# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: Your Name <your.email@student.42.fr>        +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2024/01/01 00:00:00 by Your Name         #+#    #+#             #
#   Updated: 2024/01/01 00:00:00 by Your Name        ###   ########.fr       #
#                                                                            #
# ************************************************************************** #

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Source files
SRCS = get_next_line.c main.c
SRCS_BONUS = get_next_line_bonus.c main_bonus.c

# Object files
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

# Target executable
NAME = get_next_line
NAME_BONUS = get_next_line_bonus

# Default target
all: $(NAME)

# Compile the program
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Clean everything (objects and executable)
fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

# Rebuild everything
re: fclean all

# Bonus targets
bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS)

# Test bonus with different buffer sizes
test_bonus1: CFLAGS += -DBUFFER_SIZE=1
test_bonus1: bonus
	./$(NAME_BONUS)

test_bonus42: CFLAGS += -DBUFFER_SIZE=42
test_bonus42: bonus
	./$(NAME_BONUS)

test_bonus100: CFLAGS += -DBUFFER_SIZE=100
test_bonus100: bonus
	./$(NAME_BONUS)

test_bonus1000: CFLAGS += -DBUFFER_SIZE=1000
test_bonus1000: bonus
	./$(NAME_BONUS)

# Run all bonus tests
test_bonus: test_bonus1 test_bonus42 test_bonus100 test_bonus1000

# Test with different buffer sizes
test1: CFLAGS += -DBUFFER_SIZE=1
test1: re
	./$(NAME)

test42: CFLAGS += -DBUFFER_SIZE=42
test42: re
	./$(NAME)

test100: CFLAGS += -DBUFFER_SIZE=100
test100: re
	./$(NAME)

test1000: CFLAGS += -DBUFFER_SIZE=1000
test1000: re
	./$(NAME)

# Run all tests
test: test1 test42 test100 test1000

# Phony targets (not actual files)
.PHONY: all clean fclean re test test1 test42 test100 test1000 bonus test_bonus test_bonus1 test_bonus42 test_bonus100 test_bonus1000 