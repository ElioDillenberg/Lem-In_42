# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edillenb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 11:28:49 by edillenb          #+#    #+#              #
#    Updated: 2019/07/18 13:29:25 by edillenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Werror -Wextra
CC = gcc

SOURCES = $(addsuffix .c, ft_memset ft_bzero ft_memcpy ft_memccpy ft_memmove \
		  ft_memmove ft_memchr ft_memcmp ft_strlen ft_strdup ft_strcpy \
		  ft_strncpy ft_strcat ft_strncat ft_strlcat ft_strchr ft_strstr \
		  ft_strnstr ft_strcmp ft_strncmp ft_atoi ft_isalpha ft_isdigit \
		  ft_isalnum ft_isascii ft_isprint ft_toupper ft_tolower ft_memalloc \
		  ft_memdel ft_strnew ft_strdel ft_strclr ft_striter ft_striteri \
		  ft_strmap ft_strmapi ft_strequ ft_strnequ ft_strsub ft_strjoin \
		  ft_strtrim ft_strsplit ft_itoa ft_putchar ft_putstr ft_putendl \
		  ft_putnbr ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd \
		  ft_lstnew ft_lstdelone ft_lstdel ft_lstadd ft_lstiter ft_lstmap \
		  ft_display_file ft_lstrev ft_lstputstr ft_lstlen ft_putstrclr \
		  get_next_line_multi get_next_line ft_bitoa ft_free_stropt ft_itoa \
		  ft_hexatoa ft_lltoa ft_llutoa ft_octatoa ft_po ft_sqrt ft_str_add \
		  ft_swap ft_strjoinfr ft_str_up ft_printf convert flag float_a \
		  float_b cast_arg malloc_str fill_str tools fill_float floatools \
		  color ft_strrchr)

OBJ = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) Makefile libft.h ft_printf.h
	@$(CC) $(CFLAGS) -c $(SOURCES)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
