#include "../inc/minishell.h"

t_args_exec	*init_args_exec(void)
{
	t_args_exec	*args_exec;
	char		**path;
	char		**cmd1;
	char		**cmd2;
	char		**cmd3;
	char		***tab_args;

	args_exec = ft_malloc(sizeof(t_args_exec));
	tab_args = ft_malloc(sizeof(char **) * 3);
	cmd1 = ft_malloc(sizeof(char *) * 3);
	cmd2 = ft_malloc(sizeof(char *) * 3);
	cmd3 = ft_malloc(sizeof(char *) * 3);
	cmd1[0] = "touch";
	cmd1[1] = "bonjour";
	cmd1[2] = NULL;
	cmd2[0] = "ls";
	cmd2[1] = "-l";
	cmd2[2] = NULL;
	cmd3[0] = "wc";
	cmd3[1] = "-l";
	cmd3[2] = NULL;
	tab_args[0] = cmd1;
	tab_args[1] = cmd2;
	tab_args[2] = cmd3;
	args_exec->tab_args = tab_args;
	path = ft_split(getenv("PATH"), ':');
	args_exec->path = path;
	return (args_exec);
}

void	ft_exec(t_args_exec args_exec, int ind_cmd)
{
	execve(args_exec.path_cmd, \
		args_exec.tab_args[ind_cmd], args_exec.path);
}

int	*init_pipes(int n_pipe)
{
	int	i;
	int	*pipe_fds;

	i = 0;
	pipe_fds = ft_malloc(sizeof(int) * (2 * n_pipe));
	if (!pipe_fds)
		ft_error(ERR_MALLOC, NULL);
	while (i < n_pipe)
	{
		pipe(pipe_fds + 2 * i);
		//differentes erreurs intressantes de pipe
		i++;
	}
	return (pipe_fds);
}

void	ft_close_pipes(t_exec_data *data)
{
	int	i;

	i = 0;
	while (i < (data->n_cmds - 1) * 2)
	{
		close(data->pipe_fds[i]);
		i++;
	}
}

int	ft_fork(t_exec_data *data)
{
	int		*pipe_fds;
	int		i;
	pid_t	*childs;
	
	childs = ft_malloc(sizeof(pid_t) * data->n_cmds);
	if (!childs)
		ft_error(ERR_MALLOC, NULL);
	pipe_fds = init_pipes(data->n_cmds - 1);
	data->pipe_fds = pipe_fds;
	i = 0;
	while (i < data->n_cmds)
	{
		childs[i] = fork();
		if (childs[i] < 0)
			ft_error(ERR_FORK, NULL);
		if (childs[i] == 0)
			ft_child(data, i);
		i++;
	}
	data->childs = childs;
	ft_close_pipes(data);
	return (ft_wait(data));
}

int	main(void)
{
	t_args_exec	*args_exec;
	t_exec_data	data;

	ft_garbage_collector(INIT, NULL);
	args_exec = init_args_exec();
	data.n_cmds = 3;
	data.args_exec = args_exec;
	ft_fork(&data);
	ft_close_pipes(&data);
	ft_garbage_collector(END, NULL);
}
