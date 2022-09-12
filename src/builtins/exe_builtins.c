/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:46:51 by mvue              #+#    #+#             */
/*   Updated: 2022/09/12 20:21:31 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	create_all_out_builtin(t_exec_data *data, char **outfiles)
{
	int	i;
	int	outfile;

	i = 0;
	if (!outfiles[1])
		return (1);
	while (outfiles[i + 1])
	{
		outfile = open(outfiles[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (outfile == -1)
		{
			if (access(outfiles[i], W_OK) == -1)
				return (ft_error_no_exit(ERR_PERM_DENIED, \
					outfiles[i], data), 0);
			else
				return (ft_error_no_exit(ERR_PERROR, \
					"Open failed", data), 0);
		}
		if (close(outfile) == -1)
			return (ft_error_no_exit(ERR_PERROR, \
				"Close failed", data), 0);
		i++;
	}
	return (1);
}

int	open_all_in_builtin(t_exec_data *data, char **infiles)
{
	int	i;
	int	infile;

	i = 0;
	if (!infiles[1])
		return (1);
	while (infiles[i])
	{
		infile = open(infiles[i], O_RDONLY);
		if (infile == -1)
		{
			if (access(infiles[i], F_OK) == -1)
				return (ft_error_no_exit(ERR_NO_FILE, infiles[i], data), 0);
			else if (access(infiles[i], R_OK) == -1)
				return (ft_error_no_exit(ERR_PERM_DENIED, infiles[i], data), 0);
			else
				return (ft_error_no_exit(ERR_PERROR, "Open failed", data), 0);
		}
		if (close(infile) == -1)
			return (ft_error_no_exit(ERR_PERROR, "Close failed", data), 0);
		i++;
	}
	return (1);
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env") \
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit") \
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "cd") \
		|| !ft_strcmp(cmd, "export"))
		return (1);
	return (0);
}

static void	launch_builtin(t_exec_data *data, char *cmd)
{
	if (!ft_strcmp(cmd, "pwd"))
		ft_pwd(data);
	if (!ft_strcmp(cmd, "cd"))
		ft_cd(data);
	if (!ft_strcmp(cmd, "exit"))
		ft_exit(data);
	if (!ft_strcmp(cmd, "echo"))
		ft_echo(data);
	if (!ft_strcmp(cmd, "env"))
		ft_env(data);
	if (!ft_strcmp(cmd, "unset"))
		ft_unset(data);
	if (!ft_strcmp(cmd, "export"))
		ft_export(data);
}

void	exe_builtin(t_exec_data *data)
{
	char	*cmd;

	cmd = data->args_exec->tab_args[0];
	data->fd_out_builtin = 1;
	if (data->n_cmds == 1)
	{
		if (*data->tab_parse[0].infile)
			if (!builtin_in(data, 1))
				return ;
		if (*data->tab_parse[0].outfile)
			if (!builtin_out(data, 1))
				return ;
		if (data->pipes)
			ft_close_pipes(data);
		launch_builtin(data, cmd);
		if (*data->tab_parse[0].outfile)
			close(data->fd_out_builtin);
	}
	else
	{
		launch_builtin(data, cmd);
	}
}
