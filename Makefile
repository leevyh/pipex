# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 14:55:16 by lkoletzk          #+#    #+#              #
#    Updated: 2023/05/18 12:10:22 by lkoletzk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus

SRCS = 	srcs/main.c \
		srcs/utils.c \
		srcs/execve.c \
		srcs/pipex.c 

OBJS = $(SRCS:.c=.o)

SRCS_BONUS = 	bonus/main_bonus.c \
				srcs/utils.c \
				srcs/execve.c \
				bonus/pipex_bonus.c

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

LIBFT_DIR = libft
LIBFT = libft/libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@echo "\n Mandatory compilation: OK\n"

bonus: $(LIBFT) $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBFT)
	@echo "\n Bonus compilation: OK\n"

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re
