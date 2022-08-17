#ifndef MINISELL_H
# define MINISELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
#include <sys/wait.h>
# include "../libft/libft.h"

#define EXISTS 10
#define ACCESSIBLE 11
#define	ERR_MALLOC 12
#define	ERR_NOT_FOUND 13
#define ERR_NO_FILE 14
#define ERR_PERM_DENIED 15
#define	ERR_FORK 16

extern int exit_stat;

typedef struct s_args_exec
{
	char	*path_cmd;
	char	***tab_args;
	char 	**path;
}	t_args_exec;

typedef struct s_exec_data
{
	pid_t		*childs;
	int			*pipe_fds;
	t_args_exec *args_exec;
	int			n_cmds;
}	t_exec_data;

//error.c
void	ft_error(int error_code, char *to_print);

//path.c
char	*get_path_cmd(char **split_path, char *cmd);

//utils.c
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_wait(t_exec_data *data);

//pipe.c
void	ft_exec(t_args_exec args_exec, int ind_cmd);

//childs.c 
void	ft_child(t_exec_data *exec_data, int ind_cmd);

#endif