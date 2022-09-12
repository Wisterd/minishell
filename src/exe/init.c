/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:15:54 by mvue              #+#    #+#             */
/*   Updated: 2022/09/09 01:58:07 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_pipes_until(int *pipes)
{
	int	i;

	i = 0;
	while (pipes[i] != -1)
	{
		if (close(pipes[i]) == -1)
			ft_error(ERR_PERROR, "Close error", NULL);
		i++;
	}
}

int	*init_pipes(t_exec_data *data)
{
	int	i;
	int	*pipes;
	int	n_pipes;

	if (data->n_cmds == 1)
		return (NULL);
	n_pipes = data->n_cmds - 1;
	i = 0;
	pipes = ft_malloc(sizeof(int) * (2 * n_pipes));
	if (!pipes)
		ft_error(ERR_MALLOC, NULL, NULL);
	while (i < n_pipes)
	{
		if (pipe(pipes + 2 * i) == -1)
		{
			pipes[i * 2] = -1;
			close_pipes_until(pipes);
			ft_error(ERR_PERROR, "Pipe failed", NULL);
		}
		i++;
	}
	return (pipes);
}

void	init_data(t_exec_data *data)
{
	int			*pipes;
	t_args_exec	*args_exec;

	args_exec = ft_malloc(sizeof(t_args_exec));
	if (!args_exec)
		ft_error(ERR_MALLOC, NULL, data);
	data->args_exec = args_exec;
	data->n_cmds = data->tab_parse->nb_cmd;
	data->kill_heredoc = 0;
	look_for_heredocs(data);
	pipes = init_pipes(data);
	data->pipes = pipes;
}
