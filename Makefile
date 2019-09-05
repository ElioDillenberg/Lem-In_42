# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edillenb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/27 16:42:47 by edillenb          #+#    #+#              #
#    Updated: 2019/07/29 16:01:51 by edillenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

CFLAGS = -Wall -Werror -Wextra -g
CC = gcc
LIBFT = libft/libft.a

OBJDIR = objs
SRCDIR = srcs

SC = $(addsuffix .c, lem_in get_parsing_tools parsing  buffer \
	   is_parsing_tools is_tunnel free path util_path util bfs util_bfs cut \
		result options)

SRCS = $(addprefix $(SRCDIR)/, $(SC))
OBJS = $(addprefix $(OBJDIR)/, $(SC:.c=.o))
INCLS = $(addprefix ./incls/, $(addsuffix .h, lem_in))

GREEN = \033[01;32m
BLUE = \033[01;34m
RED = \033[01;31m
YELLOW = \033[01;33m
MAGENTA = \033[35m
BLACK = \033[30m
NOCOLOR = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(INCLS) Makefile
	@echo "🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 "
	@echo "🔫                                                               🔫 $(MAGENTA)"
	@echo "🔫   [ auteurs :  edillenb && thallot ]                          🔫 $(BLUE)"
	@echo "🔫                   ___                                         🔫 "
	@echo "🔫            |     |     |\   /|         |  |\   |              🔫 "
	@echo "🔫            |     |__   | \ / |         |  | \  |              🔫 "
	@echo "🔫            |     |     |     |         |  |  \ |              🔫 "
	@echo "🔫            |___  |___  |     |  _____  |  |   \|              🔫 "
	@echo "🔫                                                               🔫 "
	@echo "🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 $(BLACK)"
	@echo "$(BLUE)⚡️ COMPILATION DE L'EXECUTABLE LEM_IN. . . . . . . $(YELLOW)"
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -o $(NAME)
	@echo "$(GREEN)TOUT EST -----------------------------------> OK$(NOCOLOR)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	    $(CC) -g3 $(CFLAGS) -c -o $@ $<

$(LIBFT): FORCE
	@echo "$(BLUE)⚡️ CHECKING LIBFT.A. . . . . . . . . . . . . . . . $(YELLOW)"
	@make -C libft/
	@echo "$(NOCOLOR)"

FORCE:

clean:
	make clean -C libft
	@echo "$(BLUE)⚡️ SUPPR DES .O . . . . . . . . . . . . . . . . . . .$(RED)"
	rm -f $(OBJS)
	@echo "$(GREEN)TOUT EST ----------------------------------> OK$(NOCOLOR)"

fclean: clean
	make fclean -C libft
	@echo "$(BLUE)⚡️ SUPPR DE L'EXECUTABLE . . . . . . . . . . . . . .$(RED)"
	rm -f $(NAME)
	@echo "$(GREEN)TOUT EST -----------------------------------> OK$(BLACK)"

re: fclean all
	@echo "🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫  $(BLUE)ET C'EST REPARTI ! 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 "
	@echo "$(BLUE)⚡️ RELINK . . . . . . . . . . . . . . ."
	@echo "$(GREEN)TOUT EST ---------------------------> OK$(NOCOLOR)"

.PHONY: all clean fclean re
