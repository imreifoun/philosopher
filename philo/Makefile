# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: areifoun <areifoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 14:44:10 by areifoun          #+#    #+#              #
#    Updated: 2023/06/22 20:16:57 by areifoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SOURCES = ./src

OBJECTS = ./obj

INCLUDE = ./inc

LIBTH = -lpthread

CC = CC

UFLAGS = -Wall -Werror -Wextra

SRC  = philosopher.c link_outils.c outils.c ft_threads.c extra_outils.c ft_think_sleep.c

OBJ = $(addprefix $(OBJECTS)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(UFLAGS) $(OBJ) -o $@
	
$(OBJECTS)/%.o : $(SOURCES)/%.c $(INCLUDE)/philosopher.h
	@mkdir -p $(dir $@)
	$(CC) $(UFLAGS) -c $< -o $@
	
clean: 
	@-rm -rf $(OBJECTS)

fclean: clean
	@-rm -rf $(NAME)

re: fclean all

