#ifndef MINISELL_H
# define MINISELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include "../libft/libft.h"

#define EXISTS 10
#define ACCESSIBLE 11
#define	ERR_MALLOC 12
#define	ERR_NOT_FOUND 13
#define ERR_NO_FILE 14
#define ERR_PERM_DENIED 15

extern int exit_stat;

//error.c
void	ft_error(int error_code, char *to_print);

//path.c
char	*get_path_cmd(char **split_path, char *cmd);

//utils.c
char	*ft_strjoin_free(char *s1, char *s2);

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