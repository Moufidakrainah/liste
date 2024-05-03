# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoan <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 10:26:38 by mdoan             #+#    #+#              #
#    Updated: 2024/04/23 14:53:26 by mdoan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME				= minishell

# Directories
INC					= inc/
SRC_DIR				= src/
OBJ_DIR				= obj/

# Compiler and CFlags
CC					= cc
CFLAGS				= -Wall -Wextra -Werror 
LDFLAGS				= -lreadline 
#j'ai ajoute LDFLAGS parce que -lreadline est un linker alors que -Wall -Wextra -Werror sont des options de compilation

RM					= rm -f

FILES				= builtins expand ft_cd ft_split_repos ft_split main utils

# Create full paths for source and object files
OBJS				= $(FILES:%=%.o)
TARGET				= $(addprefix $(OBJ_DIR), $(OBJS))

all:				$(NAME)		

$(NAME):			$(OBJ_DIR) $(TARGET)
					@$(CC) $(TARGET) -o $(NAME) -I $(INC) $(LDFLAGS)

# Compile object files from source files
$(OBJ_DIR)%.o:		$(SRC_DIR)%.c 
					@mkdir -p $(@D)
					@$(CC) -c $< -o $@ -I$(INC) $(CFLAGS)

$(OBJ_DIR) :
					mkdir -p $(OBJ_DIR)

clean:
					@$(RM) -r $(OBJ_DIR)
			
fclean:				clean
					@$(RM) $(NAME)

re:					fclean all

# Phony targets represent actions not files
.PHONY:				start all clean fclean re

