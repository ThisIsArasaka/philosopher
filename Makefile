# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/21 23:54:43 by olardeux          #+#    #+#              #
#    Updated: 2024/07/22 08:22:23 by olardeux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
SRC_FILE = main.c parsing.c init.c thread.c utils.c action.c philo.c
OBJ_FILE = $(SRC_FILE:.c=.o)
SRC_PATH = src/
OBJ_PATH = obj/
SRC = $(addprefix $(SRC_PATH), $(SRC_FILE))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILE))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "Compilation done"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Object files created"

clean:
	@rm -rf $(OBJ_PATH)
	@echo "Object files deleted"

fclean: clean
	@rm -f $(NAME)
	@echo "Binary file deleted"

re: fclean all

.PHONY: all clean fclean re
	