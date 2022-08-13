#ifndef MINISELL_H
# define MINISELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include "../libft/libft.h"

#define EXISTS 10;
#define ACCESSIBLE 11;

extern int exit_stat;

void	ft_error(int error_code, char *to_print);

typedef struct s_tab
{
	char			**tab;
	struct s_tab	*next;
	struct s_tab	*prev;
}	t_tab;

typedef struct s_args_exec
{
	char	**path_cmds;
	t_tab	*tab_args;
	char 	**path;
}	t_args_exec;

#endif