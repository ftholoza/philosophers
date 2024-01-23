# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 20:16:15 by ftholoza          #+#    #+#              #
#    Updated: 2024/01/11 20:31:35 by ftholoza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Werror -Wextra 
SRCS = $(addprefix srcs/, $(SRC))
SRC = main.c ft_atoi.c ft_isdigit.c ft_gettime.c routine.c actions.c set_struct.c control.c ft_strncmp.c
OBJ = $(SRC:.c=.o)
NAME = philo

re : fclean $(NAME)
$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)
$(OBJ) : $(SRCS)
	$(CC) $(FLAGS) -c $(SRCS) -I philosophers.h 
clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)
