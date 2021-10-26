# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-haya <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/19 23:25:34 by mel-haya          #+#    #+#              #
#    Updated: 2019/10/23 18:34:37 by mel-haya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

NAME = libft.a
FLAGS = -Wall -Werror -Wextra
SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c 
O = $(SRC:.c=.o)

all: $(NAME)

$(NAME): 
	@gcc $(SRC) -c $(FLAGS)
	@ar rc $(NAME) $(O)
clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)

re:	fclean all
