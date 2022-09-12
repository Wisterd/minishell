/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_in_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:21:09 by mvue              #+#    #+#             */
/*   Updated: 2022/09/12 20:22:07 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_access_builtin_in(int ind_last, t_exec_data *data)
{
	if (access(data->tab_parse[data->ind_cmd].infile[ind_last], \
		F_OK) == -1)
		return (ft_error_no_exit(ERR_NO_FILE, \
			data->tab_parse[data->ind_cmd].infile[ind_last], data), 0);
	else if (access(data->tab_parse[data->ind_cmd].infile[ind_last], \
		R_OK) == -1)
		return (ft_error_no_exit(ERR_PERM_DENIED, \
			data->tab_parse[data->ind_cmd].infile[ind_last], data), 0);
	else
		return (ft_error_no_exit(ERR_PERROR, "Open failed", data), 0);
}

int	builtin_in(t_exec_data *data, int mode)
{
	int	fd_in;
	int	ind_last;

	fd_in = STDIN_FILENO;
	if (!open_all_in_builtin(data, data->tab_parse[data->ind_cmd].infile))
		return (0);
	ind_last = get_ind_last_redir(data->tab_parse[0].inredir);
	if (data->tab_parse[data->ind_cmd].infile[0])
	{
		fd_in = open(data->tab_parse[data->ind_cmd].infile[ind_last], O_RDONLY);
		if (fd_in == -1)
			return (check_access_builtin_in(ind_last, data));
		if (mode == 1)
			close(fd_in);
	}
	return (1);
}

static int	check_access_builtin_out(int ind_last, t_exec_data *data)
{
	if (access(data->tab_parse[data->ind_cmd].outfile[0], W_OK) == -1)
		return (ft_error_no_exit(ERR_PERM_DENIED, \
			data->tab_parse[data->ind_cmd].outfile[ind_last], data), 0);
	else
		return (ft_error_no_exit(ERR_PERROR, "Open failed", data), 0);
}

int	builtin_out(t_exec_data *data, int mode)
{
	int	fd_out;
	int	ind_last;

	fd_out = STDOUT_FILENO;
	if (!create_all_out_builtin(data, data->tab_parse[data->ind_cmd].outfile))
		return (0);
	ind_last = get_ind_last_redir(data->tab_parse[data->ind_cmd].outredir);
	if (data->tab_parse[data->ind_cmd].outfile[0])
	{
		if (!ft_strncmp(data->tab_parse[data->ind_cmd].outredir[ind_last], \
			">>", 2))
			fd_out = open(data->tab_parse[data->ind_cmd].outfile[ind_last], \
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd_out = open(data->tab_parse[data->ind_cmd].outfile[ind_last], \
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out == -1)
			return (check_access_builtin_out(ind_last, data));
	}
	if (mode == 1)
		data->fd_out_builtin = fd_out;
	return (1);
}
