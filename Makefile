NAME = minishell
RM = rm -f
DEPS = Makefile ./inc/minishell.h

# compilation
CC = cc
FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

# directories
SRCDIR	:=	./src
INCDIR	:=	./inc
OBJDIR	:=	./obj

# sources and objects
SRC = main.c \

OBJ := $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
SRC	:= $(addprefix $(SRCDIR)/, $(SRC))

# libft
LIBFT_PATH = ./libft/libft.a
LIBDIR	=	./libft/
LIBFTINC = -I ./libft
LIBFT_LINK = -L ./libft -l ft -l pthread

# rules
all: obj $(LIBFT_PATH) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(DEPS)
	$(CC) $(FLAGS) $(LIBFTINC) -I $(INCDIR) -o $@ -c $<

$(LIBFT_PATH):
	@make -C $(LIBDIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT_LINK) -o $(NAME) $(FLAGS)

clean:
	rm -rf $(OBJDIR)
	make -C $(LIBDIR) clean

fclean: clean
	rm -rf $(LIBFT_PATH)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re