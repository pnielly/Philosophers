# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <pnielly@student.42.fr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/03 17:48:57 by user42            #+#    #+#              #
#    Updated: 2021/07/22 16:36:37 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------- Executables
NAME=philo
NAME_MORE=philo_more

# ---------- Commands
CC=gcc
FLAGS=-Wall -Wextra -Werror

# ---------- SRCS, OBJS and INC
INC=-I /includes/philo.h 
LIBS= -lpthread -D_REENTRANT

SRC_DIR=srcs/
SRC= main.c error_parsing.c utils.c utils_2.c init.c end_clear.c forks.c log.c routine.c do_sleep.c
SRC_MORE= main.c error_parsing.c utils.c utils_2.c init.c end_clear.c forks.c log_more.c routine.c do_sleep.c

OBJ_DIR=obj/
OBJ=$(addprefix $(OBJ_DIR),$(SRC:.c=.o))
OBJ_MORE=$(addprefix $(OBJ_DIR),$(SRC_MORE:.c=.o))

# ---------- Colors
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"

# ---------- Rules

all: $(NAME)
	@printf $(GREEN)" -------------- philo compiled   ----------------\n"

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LIBS) $(INC)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@printf $(CYAN)" -------------- Compiling $@ ---------------\n"$(EOC)
	@$(CC) $(FLAGS) -o $@ -c $<

more: $(NAME_MORE)
	@printf $(GREEN)" -------------- philo_more compiled   ----------------\n"

$(NAME_MORE): $(OBJ_MORE)
	@$(CC) $(FLAGS) $(OBJ_MORE) -o $(NAME_MORE) $(LIBS) $(INC)

clean:
	@rm -rf *.gch obj
	@printf $(RED)" -------------- Object files removed --------------\n"$(EOC)

fclean:	clean
	@rm -f $(NAME) $(NAME_MORE)
	@printf $(RED)" -------------- Executable files removed ----------\n"$(EOC)

re: fclean all

# ---------- 
