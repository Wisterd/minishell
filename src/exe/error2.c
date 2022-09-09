/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 02:31:04 by mvue              #+#    #+#             */
/*   Updated: 2022/09/09 02:32:43 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_error_no_exit(int error_code, char *to_print, t_exec_data *data)
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
	g_exit_stat = exit_stat;
}
