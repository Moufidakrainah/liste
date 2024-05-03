NAME				= minishell

# Directories
INC					= inc/
SRC_DIR				= src/
OBJ_DIR				= obj/

# Compiler and CFlags
CC					= cc
CFLAGS				= -Wall -Wextra
LDFLAGS				= -lreadline

RM					= rm -f

FILES				= builtins ft_cd ft_split_repos ft_split main utils variable

# Create full paths for source and object files
OBJS				= $(FILES:%=%.o)
TARGET				= $(addprefix $(OBJ_DIR), $(OBJS))

all:				$(NAME)		

$(NAME):			$(OBJ_DIR) $(TARGET)
					@$(CC) $(TARGET) -o $(NAME) -I $(INC) $(LDFLAGS) 

# Compile object files from source files
$(OBJ_DIR)%.o:		$(SRC_DIR)%.c 
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@ -I$(INC)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

clean:
					@$(RM) -r $(OBJ_DIR)
			
fclean:				clean
					@$(RM) $(NAME)

re:					fclean all

# Phony targets represent actions not files
.PHONY:				start all clean fclean re
