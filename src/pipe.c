#include "../inc/minishell.h"

t_args_exec	init_args_exec(void)
{
	t_args_exec	args_exec;
	char		**path = ft_split(getenv("PATH"), ':');
	char		*path_cmds[3] = {get_path_cmd(path, "echo"), \
		get_path_cmd(path, "ls"), get_path_cmd(path, "wc")};
	char		*cmd1[3] = {"echo", "bonjour", NULL};
	char		*cmd2[3] = {"ls", "-l", NULL};
	char		*cmd3[3] = {"wc", "-l", NULL};
	char		**tab_args[3];

	tab_args[0] = cmd1;
	tab_args[1] = cmd2;
	tab_args[2] = cmd3;
	args_exec.path_cmds = path_cmds;
	args_exec.path = path;
	args_exec.tab_args = tab_args;
	return (args_exec);
}

void	ft_exec(t_args_exec args_exec, int ind_cmd)
{
	execve(args_exec.path_cmds[ind_cmd], \
		args_exec.tab_args[ind_cmd], args_exec.path);
}

int	*init_pipes(int n_pipe)
{
	int	i;
	int	*pipe_fds;

	i = 0;
	pipe_fds = ft_malloc(sizeof(int) * (2 * n_pipe));
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
	while (i < data->n_cmds - 1)
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
	t_args_exec	args_exec;
	int	*pipe_fds;

	ft_garbage_collector(INIT, NULL);
	args_exec = init_args_exec();
	pipe_fds = init_pipes(2);
	ft_garbage_collector(END, NULL);
}
