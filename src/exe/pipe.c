#include "../../inc/minishell.h"

void	ft_exec(t_args_exec args_exec)
{
	if (execve(args_exec.path_cmd, args_exec.tab_args, \
		args_exec.tab_env) == -1)
		ft_error(ERR_PERROR, "Execve failed", NULL);
}

void	fill_pipes(t_exec_data *data, int *pipes)
{
	static int	mem_l_pipe = 0;
	static int	mem_r_pipe = 2;
	int			temp;

	if (data->ind_cmd == 0 || data->ind_cmd == data->n_cmds - 1)
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
	int		i;
	pid_t	*childs;
	
	if (data->n_cmds == 1)
	{
		data->args_exec->tab_args = data->tab_parse[0].tab_args;
		data->ind_cmd = 0;
		if (!is_builtin(data->args_exec->tab_args[0]))
			return (exe_one_cmd(data));
		else
		{
			// g_exit_stat = 0;
			exe_builtin(data);
			return (g_exit_stat);
		}
	}
	else
	{
		childs = ft_malloc(sizeof(pid_t) * data->n_cmds);
		if (!childs)
			ft_error(ERR_MALLOC, NULL, NULL);
		i = -1;
		while (++i < data->n_cmds)
		{
			data->ind_cmd = i;
			fill_pipes(data, data->pipes);
			childs[i] = fork();
			if (childs[i] < 0)
				ft_error(ERR_PERROR, "Fork failed", data->pipes);
			if (childs[i] == 0)
				ft_child(data);
		}
		data->childs = childs;
		ft_close_pipes(data->pipes, -1);
		return (ft_wait(data));
	}
	return (0);
}

//TODO :
//gestion d erreur
//heredocs
//pas besoin de gerer les = sans export
//executer les builtins au lieu de les chercher dans le path
//env -i
//write error: No space left on device pour tous les buitins qui ecrivent
//attention quand on exec un builtin dans le parent on doit free les variables permanantes en cas d'erreur, on le fait pas 
