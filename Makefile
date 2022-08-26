NAME = minishell
CFLAGS =  -Wall -Wextra -Werror -g #-fsanitize=thread
DEPS = $(INCLUDES)minishell.h Makefile
INCLUDES = inc/
SRC_DIR = src/
OBJ_DIR = obj/
LIBFT =  -L ./libft -lft

	exe/error.c \
	signal.c \
SRC_FILES = $(addprefix $(SRC_DIR), \
	exe/path.c \
	exe/pipe.c \
	exe/error.c \
	exe/utils.c \
	exe/childs.c \
	exe/redirs.c \
	exe/init.c \
	builtins/env.c \
	builtins/unset.c \
	main.c \
	parsing.c \
	lexer.c error.c lexer2.c utilitaires_parsing.c valide_lexer.c \
	parse_to_exec.c \
	signal.c)

OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_FILES))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEPS)
	@if [ ! -d "$(dir $@)" ]; then mkdir $(dir $@); fi
	gcc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(DEPS)
	$(MAKE) -C libft/
	gcc $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

all : $(NAME)

clean :
	$(MAKE) clean -C libft/
	rm -rf $(OBJ_DIR)

fclean : clean
	$(MAKE) fclean -C libft/
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
