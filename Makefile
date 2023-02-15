

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/08 19:44:23 by oboutarf          #+#    #+#              #
#    Updated: 2023/02/05 06:47:15 by oboutarf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= cub3Dparser

CC 				= gcc -g3 -Wall -Wextra -Werror -MMD # -fsanitize=address

OBJ				= $(SRCS:.c=.o)

DEP				= $(SRCS:.c=.d)

SRCS 			= main.c

SRCH_INCLDS 	= -Iincld

RM				= rm -rf

all:        $(NAME)

%.o: %.c
			$(CC) $(SRCH_INCLDS) -c $< -o $@

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

clean:
			$(RM) $(OBJ)
			$(RM) $(DEP)

fclean:     clean
			$(RM) $(NAME)

re:         fclean $(NAME)
