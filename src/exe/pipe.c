/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:16:14 by mvue              #+#    #+#             */
/*   Updated: 2022/09/09 01:42:19 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exec(t_args_exec args_exec)
{
	if (execve(args_exec.path_cmd, args_exec.tab_args, \
		args_exec.tab_env) == -1)
		ft_error(ERR_PERROR, "Execve failed", NULL);
}

void	fill_pipes(t_exec_data *data)
{
	if (data->ind_cmd == 0)
	{
		data->l_pipe = NULL;
		data->r_pipe = data->pipes;
	}
	else if (data->ind_cmd == data->n_cmds - 1)
	{
		data->l_pipe = data->pipes + data->ind_cmd * 2 - 2;
		data->r_pipe = NULL;
	}
	else
	{
		data->l_pipe = data->pipes + data->ind_cmd * 2 - 2;
		data->r_pipe = data->pipes + data->ind_cmd * 2;
	}
}

void	ft_close_pipes(t_exec_data *data)
{
	int	i;

	i = 0;
	while (i < (data->n_cmds - 1) * 2)
	{
		if (close(data->pipes[i]) == -1)
			ft_error(ERR_PERROR, "Close error", data);
		i++;
	}
	ft_free(data->pipes);
	data->pipes = NULL;
}

void	launch_children(t_exec_data *data)
{
	pid_t	*childs;
	int		i;

	childs = ft_malloc(sizeof(pid_t) * data->n_cmds);
	if (!childs)
		ft_error(ERR_MALLOC, NULL, NULL);
	i = -1;
	signal(SIGINT, SIG_IGN);
	while (++i < data->n_cmds)
	{
		data->ind_cmd = i;
		fill_pipes(data);
		childs[i] = fork();
		if (childs[i] < 0)
			ft_error(ERR_PERROR, "Fork failed", data);
		if (childs[i] == 0)
			ft_child(data);
	}
	data->childs = childs;
	ft_close_pipes(data);
}

int	ft_fork(t_exec_data *data)
{
	if (data->kill_heredoc == 1)
		return (130);
	if (data->n_cmds == 1)
	{
		data->args_exec->tab_args = data->tab_parse[0].tab_args;
		data->ind_cmd = 0;
		if (!is_builtin(data->args_exec->tab_args[0]))
			return (exe_one_cmd(data));
		else
		{
			exe_builtin(data);
			return (g_exit_stat);
		}
	}
	else
	{
		launch_children(data);
		return (ft_wait(data));
	}
	return (0);
}

//TODO :
//echo $ comme premier test, invalid read
///mnt/nfs/homes/mvue/Documents/minishell: Is a directory err 126
//ft_error avec data->pipes, bien initialiser data->pipes a NULL et 
//le remettre a nul apres avoir close les pipes
//write error: No space left on device pour tous les buitins qui ecrivent
//signaux heredocs
//chercher tous les ft_malloc pour verifier qu'ils sont proteges
//check qu'on remet bien g_exit_stat a 0 quand builtins, pipes, cmds simples etc
