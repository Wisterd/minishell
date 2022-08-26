#include "../../inc/minishell.h"

void	ft_exec(t_args_exec args_exec, int ind_cmd, int *pipes)
{
	if (execve(args_exec.path_cmd, args_exec.tab_args[ind_cmd], \
		args_exec.path) == -1)
		ft_error(ERR_PERROR, "Execve failed", pipes);
}

int	*init_pipes(t_exec_data *data)
{
	int	*pipes;

	if (data->n_cmds == 1)
		return (NULL);
	pipes = ft_malloc(sizeof(int) * 4);
	if (!pipes)
		ft_error(ERR_MALLOC, NULL, NULL);
	if (pipe(pipes) == -1)
		ft_error(ERR_PERROR, "Pipe failed", NULL);
	if (pipe(pipes + 2) == -1)
	{
		if (close(pipes[0]) == -1)
			ft_error(ERR_PERROR, "Close failed", NULL);
		if (close(pipes[1]) == -1)
			ft_error(ERR_PERROR, "Close failed", NULL);
		ft_error(ERR_PERROR, "Pipe failed", NULL);
	}
	return (pipes);
}

void	fill_pipes(t_exec_data *data, int *pipes, int ind_cmd)
{
	static int	mem_l_pipe = 0;
	static int	mem_r_pipe = 2;
	int			temp;

	if (ind_cmd == 0 || ind_cmd == data->n_cmds - 1)
	{
		data->l_pipe = pipes + mem_l_pipe;
		data->r_pipe = pipes;
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

void	ft_close_pipes(int	*pipes, int dont_close)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (i != dont_close)
			if (close(pipes[i]) == -1)
				ft_error(ERR_PERROR, "Close error", pipes);
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
		ft_error(ERR_MALLOC, NULL, NULL);
	pipes = init_pipes(data);
	data->pipes = pipes;
	i = -1;
	while (++i < data->n_cmds)
	{
		fill_pipes(data, pipes, i);
		childs[i] = fork();
		if (childs[i] < 0)
			ft_error(ERR_PERROR, "Fork failed", data->pipes);
		if (childs[i] == 0)
			ft_child(data, i);
	}
	data->childs = childs;
	ft_close_pipes(pipes, -1);
	return (ft_wait(data));
}

//TODO :
//gestion d erreur
//regarder d abord si je trouve la commande demandee dans le repertoire courant avant de fouiller le PATH
//cas special si une seule commande a executer (executer dans le parent et non le child)
//heredocs
//pas besoin de gerer les = sans export
//empecher qu'on puisse mettre des arguments a env en mettant un message d'erreur
//executer les builtins au lieu de les chercher dans le path

/*
int	main(int ac, char **av, char *envp[])
{
	t_args_exec	*args_exec;
	t_exec_data	data;

	ft_garbage_collector(INIT, NULL);
	args_exec = init_args_exec();
	data.n_cmds = 4;
	data.args_exec = args_exec;
	set_inoutfies(&data);
	set_redirs(&data);
	ft_fork(&data);
	ft_garbage_collector(END, NULL);

	t_env	*l_env;
	(void)	av;

	if (ac == 1)
	{
		l_env = init_env(envp);
		printf(l_env->var_content);
	}
}
*/