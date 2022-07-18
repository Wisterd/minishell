NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=thread
DEPS = $(INCLUDES)minishell.h Makefile
INCLUDES = inc/
SRC_DIR = src/
OBJ_DIR = obj/

SRC_FILES = $(addprefix $(SRC_DIR), main.c)
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_FILES))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@if [ ! -d "$(dir $@)" ]; then mkdir -p $(dir $@); fi
	gcc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(DEPS)
	gcc $(CFLAGS) $(OBJ) $(FT_PRINTF) -o $(NAME)

all : $(NAME)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re

