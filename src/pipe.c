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
	cmd2[0] = "cat";
	cmd2[1] = "bonjour";
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

/*
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
*/

int	*init_pipes(t_exec_data *data)
{
	int	*pipes;

	if (data->n_cmds == 1)
		return (NULL);
	pipes = ft_malloc(sizeof(int) * 4);
	if (!pipes)
		ft_error(ERR_MALLOC, NULL);
	pipe(pipes);
	//differentes erreurs intressantes de pipe
	pipe(pipes + 2);
	//differentes erreurs intressantes de pipe
	return (pipes);
}

void	fill_pipes(t_exec_data *data, int *pipes, int ind_cmd)
{
	static int	mem_l_pipe = 0;
	static int	mem_r_pipe = 2;
	int			temp;

	if (ind_cmd == 0)
	{
		data->l_pipe = NULL;
		data->r_pipe = pipes;
	}
	else if (ind_cmd == data->n_cmds - 1)
	{
		data->l_pipe = pipes + mem_l_pipe;
		data->r_pipe = NULL;
	}
	else
	{
		data->l_pipe = pipes + mem_l_pipe;
		data->r_pipe = pipes + mem_r_pipe;
		temp = mem_l_pipe;
		mem_l_pipe = mem_r_pipe;
		mem_r_pipe = temp;
	}
}

void	ft_close_pipes(int	*pipes)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		close(pipes[i]);
		i++;
	}
	ft_free(pipes);
}

int	ft_fork(t_exec_data *data)
{
	int		*pipes;
	int		i;
	pid_t	*childs;
	
	childs = ft_malloc(sizeof(pid_t) * data->n_cmds);
	if (!childs)
		ft_error(ERR_MALLOC, NULL);
	pipes = init_pipes(data);
	i = -1;
	while (++i < data->n_cmds)
	{
		fill_pipes(data, pipes, i);
		childs[i] = fork();
		if (childs[i] < 0)
			ft_error(ERR_FORK, NULL);
		if (childs[i] == 0)
			ft_child(data, i);
	}
	data->childs = childs;
	ft_close_pipes(pipes);
	return (ft_wait(data));
}

//TODO :
//gestion d erreur
//regarder d abord si je trouve la commande demandee dans le repertoire courant avant de fouiller le PATH
//cas special si une seule commande a executer (executer dans le parent et non le child)
//redirections

int	main(void)
{
	t_args_exec	*args_exec;
	t_exec_data	data;

	ft_garbage_collector(INIT, NULL);
	args_exec = init_args_exec();
	data.n_cmds = 3;
	data.args_exec = args_exec;
	ft_fork(&data);
	ft_garbage_collector(END, NULL);
}