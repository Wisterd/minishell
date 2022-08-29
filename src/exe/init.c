#include "../../inc/minishell.h"

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

void	init_data(t_exec_data *data)
{
	int			*pipes;
	t_args_exec	*args_exec;

	args_exec = ft_malloc(sizeof(t_args_exec));
	data->args_exec = args_exec;
	data->args_exec->path = ft_split(ft_getenv("PATH", data), ':');
	data->n_cmds = data->tab_parse->nb_cmd;
	pipes = init_pipes(data);
	data->pipes = pipes;
}