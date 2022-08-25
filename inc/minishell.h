#ifndef MINISELL_H
# define MINISELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <linux/limits.h>
# include "../libft/libft.h"

#define EXISTS 10
#define ACCESSIBLE 11
#define	ERR_MALLOC 12
#define	ERR_NOT_FOUND 13
#define ERR_NO_FILE 14
#define ERR_PERM_DENIED 15
#define	ERR_PERROR 16


extern int exit_stat;

typedef struct s_args_exec
{
	char	*path_cmd;
	char	***tab_args;
	char 	**path;
}	t_args_exec;

typedef struct s_exec_data
{
	int			n_cmds;
	int			ind_cmd;
	int			*pipes;
	int			*l_pipe;
	int			*r_pipe;
	char		**infile;
	char		**outfile;
	char		**redir_in;
	char		**redir_out;
	pid_t		*childs;
	t_args_exec *args_exec;
}	t_exec_data;

typedef struct s_env
{
	struct s_env	*prev;
	struct s_env	*next;
	char			*var_name;
	char			*var_content;
}	t_env;

//EXE
//error.c
void		ft_error(int error_code, char *to_print, int *pipes);

//path.c
char		*get_path_cmd(t_exec_data *data, char *cmd);

//utils.c
char		*ft_strjoin_free(char *s1, char *s2);
int			ft_wait(t_exec_data *data);
void		ft_exit(void);
char		*ft_getcwd(t_exec_data *data);

//pipe.c
void		ft_exec(t_args_exec args_exec, int ind_cmd, int *pipes);
void		ft_close_pipes(int	*pipes, int dont_close);
int			*init_pipes(t_exec_data *data);

//childs.c 
void		ft_child(t_exec_data *exec_data, int ind_cmd);

//init.c
t_args_exec	*init_args_exec(void);
void		set_inoutfies(t_exec_data *data);
void		set_redirs(t_exec_data	*data);

//BUILTINS
//env.c
t_env		*init_env(t_exec_data *data, char **envp);
void		print_env(t_env *l_env);

#endif