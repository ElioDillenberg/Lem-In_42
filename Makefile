# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edillenb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/27 16:42:47 by edillenb          #+#    #+#              #
#    Updated: 2019/07/19 15:19:05 by edillenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

CFLAGS = -Wall -Werror -Wextra
CC = gcc
LIBFT = libft/libft.a

SRCS = $(addprefix srcs/, $(addsuffix .c, ))
OBJS = $(addprefix objs/, $(addsuffix .o, ))
INCLS = $(addprefix incls/, $(addsuffix .h, ))

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
	@echo "🔫   [ auteur :  edillenb ]                                      🔫 $(BLUE)"
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

$(LIBFT): FORCE
	@echo "$(BLUE)⚡️ CHECKING LIBFT.A. . . . . . . . . . . . . . . . $(YELLOW)"
	@make -C libft/

FORCE:

clean:
	make clean -C libft
	@echo "$(BLUE)⚡️ SUPPR DES .O . . . . . . . . . . . . . . . . . . .$(RED)"
	rm -f $(OBJ)
	@echo "$(GREEN)TOUT EST ----------------------------------> OK$(NOCOLOR)"

fclean: clean
	make fclean -C libft
	@echo "$(BLUE)⚡️ SUPPR DES EXECUTABLES . . . . . . . . . . . . . .$(RED)"
	rm -f $(NAME)
	@echo "$(GREEN)TOUT EST -----------------------------------> OK$(BLACK)"

re: fclean all
	@echo "🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫  $(BLUE)ET C'EST REPARTI ! 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 "
	@echo "$(BLUE)⚡️ RELINK . . . . . . . . . . . . . . ."
	@echo "$(GREEN)TOUT EST ---------------------------> OK$(NOCOLOR)"

.PHONY: all clean fclean re
