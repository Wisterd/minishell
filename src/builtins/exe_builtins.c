#include "../../inc/minishell.h"

static void	builtin_in(t_exec_data *data, int mode)
{
	int	fd_in;
	int	ind_last;

	fd_in = STDIN_FILENO;
	open_all_in(data, data->tab_parse[data->ind_cmd].infile);
	ind_last = get_ind_last_redir(data->tab_parse[0].inredir);
	if (data->tab_parse[data->ind_cmd].infile[0])
	{
		fd_in = open(data->tab_parse[data->ind_cmd].infile[ind_last], O_RDONLY);
		if (fd_in == -1)
		{
			if (access(data->tab_parse[data->ind_cmd].infile[ind_last], F_OK) == -1)
				ft_error(ERR_NO_FILE, data->tab_parse[data->ind_cmd].infile[ind_last], data->pipes);
			else if (access(data->tab_parse[data->ind_cmd].infile[ind_last], R_OK) == -1)
				ft_error(ERR_PERM_DENIED, data->tab_parse[data->ind_cmd].infile[ind_last], data->pipes);
			else 
				ft_error(ERR_PERROR, "Open failed", data->pipes);
		}
		if (mode == 1)
			close(fd_in);
	}
	if (mode == 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			ft_error(ERR_PERROR, "Dup2 failed", data->pipes);
	}
}

static void	builtin_out(t_exec_data *data, int mode)
{
	int	fd_out;
	int	ind_last;

	fd_out = STDOUT_FILENO;
	create_all_out(data, data->tab_parse[data->ind_cmd].outfile);
	ind_last = get_ind_last_redir(data->tab_parse[data->ind_cmd].outredir);
	if (data->tab_parse[data->ind_cmd].outfile[0])
	{
		if (!ft_strncmp(data->tab_parse[data->ind_cmd].outredir[ind_last], ">>", 2))
			fd_out = open(data->tab_parse[data->ind_cmd].outfile[ind_last], O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd_out = open(data->tab_parse[data->ind_cmd].outfile[ind_last], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out == -1)
		{
			if (access(data->tab_parse[data->ind_cmd].outfile[0], W_OK) == -1)
				ft_error(ERR_PERM_DENIED, data->tab_parse[data->ind_cmd].outfile[ind_last], data->pipes);
			else
				ft_error(ERR_PERROR, "Open failed", data->pipes);
		}
	}
	if (mode == 1)
		data->fd_out_builtin = fd_out;
	else
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			ft_error(ERR_PERROR, "Dup2 failed", data->pipes);
	}
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env") \
		|| !ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

static void	launch_builtin(t_exec_data *data, char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		ft_echo(data->tab_parse[data->ind_cmd].tab_args);
	if (!ft_strcmp(cmd, "env"))
		ft_env(data);
	if (!ft_strcmp(cmd, "unset"))
		ft_unset(data, data->tab_parse[data->ind_cmd].tab_args[1]);
}

void	exe_builtin(t_exec_data *data)
{
	char	*cmd;

	cmd = data->args_exec->tab_args[0];
	data->fd_out_builtin = 1;
	if (data->n_cmds == 1)
	{
		if (*data->tab_parse[0].infile)
			builtin_in(data, 1);
		if (*data->tab_parse[0].outfile)
			builtin_out(data, 1);
		if (data->pipes)
			ft_close_pipes(data->pipes, -1);
		launch_builtin(data, cmd);
		if (*data->tab_parse[0].outfile)
			close(data->fd_out_builtin);
	}
	else
		launch_builtin(data, cmd);
}
