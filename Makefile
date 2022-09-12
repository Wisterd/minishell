NAME = minishell
CFLAGS =  -Wall -Wextra -Werror -g #-fsanitize=thread
DEPS = $(INCLUDES)minishell.h Makefile
INCLUDES = inc/
SRC_DIR = src/
OBJ_DIR = obj/
LIBFT =  -L ./libft -lft

SRC_FILES = $(addprefix $(SRC_DIR), \
	main.c \
	exe/path.c \
	exe/pipe.c \
	exe/error.c \
	exe/error2.c \
	exe/utils.c \
	exe/childs.c \
	exe/redirs.c \
	exe/init.c \
	exe/one_cmd.c \
	exe/heredocs.c \
	exe/heredocs2.c \
	builtins/env.c \
	builtins/echo.c \
	builtins/unset.c \
	builtins/pwd.c \
	builtins/exit.c \
	builtins/cd.c \
	builtins/export.c \
	builtins/export2.c \
	builtins/exe_builtins.c \
	builtins/builtins_in_out.c \
	builtins/utils_env.c \
	parsing/parsing.c \
	parsing/lexer.c \
	parsing/error.c \
	parsing/lexer2.c \
	parsing/utilitaires_parsing.c \
	parsing/valide_lexer.c \
	parsing/init_tab_to_exec.c \
	parsing/parse_to_exec.c \
	parsing/signal.c \
	parsing/history.c \
	parsing/fuz_and_remove_lexer.c \
	parsing/quote.c \
	parsing/env_dollar.c \
	parsing/valide_lexer_dollar.c)

OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_FILES))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEPS)
	@if [ ! -d "$(OBJ_DIR)" ]; then mkdir $(OBJ_DIR); fi
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
