#ifndef MINISELL_H
# define MINISELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

#define MALLOC 0
#define FREE 1
#define END 2
#define INIT 3

typedef struct s_garbage
{
	void				*pointer;
	struct s_garbage	*next;
	struct s_garbage	*prev;
}	t_garbage;

typedef struct s_tab
{
	char			**tab;
	struct s_tab	*next;
	struct s_tab	*prev;
}	t_tab;

typedef struct s_args_exec
{
	t_tab	*tab_cmds;
	t_tab	*tab_args;
	char 	*path_cmd;
}	t_args_exec;

void	*ft_malloc(int size);
void	ft_free(void *pointer);
void	garbage_collector(int mode, void *pointer);

#endif