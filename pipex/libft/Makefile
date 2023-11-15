# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 11:51:05 by lkoletzk          #+#    #+#              #
#    Updated: 2023/05/17 12:41:49 by lkoletzk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		# ft_lstnew.c \
		# ft_lstadd_front.c \
		# ft_lstsize.c \
		# ft_lstlast.c \
		# ft_lstadd_back.c \
		# ft_lstdelone.c \
		# ft_lstclear.c \
		# ft_lstiter.c \
		# ft_lstmap.c 

OBJS = $(SRCS:.c=.o)

PRINTF = ft_printf.c \
		ft_putcsdi.c \
		ft_putunbr.c \
		ft_putxptr.c

PRINTF_OBJS = $(PRINTF:.c=.o)

GNL = get_next_line.c

GNL_OBJS = $(GNL:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -g3

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF_OBJS) $(GNL_OBJS)
	ar rcs $(NAME) $(OBJS) $(PRINTF_OBJS) $(GNL_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $< -c

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
