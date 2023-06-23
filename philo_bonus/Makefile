# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: areifoun <areifoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/15 14:44:10 by areifoun          #+#    #+#              #
#    Updated: 2023/06/22 19:34:24 by areifoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo_bonus

SOURCES = ./src

OBJECTS = ./obj

INCLUDE = ./inc

LIBTH = -lpthread

CC = CC

UFLAGS = -Wall -Werror -Wextra

SRC  = philosopher.c outils.c link_outils.c ft_semaphore.c

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

