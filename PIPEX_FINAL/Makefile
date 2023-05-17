# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 14:55:16 by lkoletzk          #+#    #+#              #
#    Updated: 2023/05/17 15:03:18 by lkoletzk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

# SRCS = 	main.c \
# 		utils.c \
# 		here_doc.c \
# 		pipex.c 

SRCS = 	main.c \
		utils.c \
		here_doc.c \
		pipex_bonus.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = libft/libft.a

CC = cc

CFLAGS = -Wall -Werror -Wextra -g3

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $< -c

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
