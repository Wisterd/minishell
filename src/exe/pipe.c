#include "../../inc/minishell.h"

void	ft_exec(t_args_exec args_exec)
{
	if (execve(args_exec.path_cmd, args_exec.tab_args, \
		args_exec.path) == -1)
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
		exe_one_cmd(data);
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
//regarder d abord si je trouve la commande demandee dans le repertoire courant avant de fouiller le PATH
//cas special si une seule commande a executer (executer dans le parent et non le child)
//heredocs
//pas besoin de gerer les = sans export
//empecher qu'on puisse mettre des arguments a env en mettant un message d'erreur
//executer les builtins au lieu de les chercher dans le path
//env -i
//write error: No space left on device pour tous les buitins qui ecrivent
//recuperer le envp pour le execve l'ait !!!
//enlever les ft_malloc et ft_free du builtin env
//attention quand on exec un builtin dans le parent on doit free les variables permanantes en cas d'erreur, on le fait pas 
