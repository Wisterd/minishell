/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:15:44 by mvue              #+#    #+#             */
/*   Updated: 2022/09/09 02:32:51 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_exit_stat = 0;

void	ft_exit_error(int exit_stat)
{
	ft_garbage_collector(END, NULL);
	ft_garbage_collector_perm(END, NULL);
	exit(exit_stat);
}

char	*check_err_1(int *exit_stat, char *to_print, int error_code)
{
	char	*error_msg;

	error_msg = "";
	if (error_code == ERR_MALLOC)
	{
		*exit_stat = 1;
		error_msg = ft_strjoin(to_print, "Malloc error\n");
	}
	if (error_code == ERR_PERROR)
	{
		*exit_stat = 1;
		perror(to_print);
	}
	return (error_msg);
}

char	*check_err_127(int *exit_stat, char *to_print, int error_code)
{
	char	*error_msg;

	error_msg = "";
	if (error_code == ERR_NOT_FOUND)
	{
		*exit_stat = 127;
		error_msg = ft_strjoin(to_print, ": command not found\n");
	}
	if (error_code == ERR_NO_FILE)
	{
		*exit_stat = 127;
		error_msg = ft_strjoin(to_print, ": No such file or directory\n");
	}
	return (error_msg);
}

char	*check_err_126(int *exit_stat, char *to_print, int error_code)
{
	char	*error_msg;

	error_msg = "";
	if (error_code == ERR_PERM_DENIED)
	{
		*exit_stat = 126;
		error_msg = ft_strjoin(to_print, ": Permission denied\n");
	}
	if (error_code == ERR_DIR)
	{
		*exit_stat = 126;
		error_msg = ft_strjoin(to_print, ": Is a directory\n");
	}
	return (error_msg);
}

void	ft_error(int error_code, char *to_print, t_exec_data *data)
{
	int		exit_stat;
	char	*error_msg;

	exit_stat = 0;
	if (error_code == ERR_MALLOC || error_code == ERR_PERROR)
		error_msg = check_err_1(&exit_stat, to_print, error_code);
	else if (error_code == ERR_NOT_FOUND || error_code == ERR_NO_FILE)
		error_msg = check_err_127(&exit_stat, to_print, error_code);
	else
		error_msg = check_err_126(&exit_stat, to_print, error_code);
	if (!error_msg)
	{
		write(2, "Malloc error\n", 13);
		ft_exit_error(1);
	}
	if (data)
		if (data->pipes)
			ft_close_pipes(data);
	write(2, error_msg, ft_strlen(error_msg));
	ft_exit_error(exit_stat);
}
