#include "../../inc/minishell.h"

static int	launch_builtin(t_exec_data *data, char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
	{
		ft_echo(data->tab_parse[data->ind_cmd].tab_args);
		return (1);
	}
	if (!ft_strcmp(cmd, "env"))
	{
		ft_env(data);
		return (1);
	}
	if (!ft_strcmp(cmd, "unset"))
	{
		ft_unset(data);
		return (1);
	}
	return (0);
}

int	exe_builtin(t_exec_data *data, int fd_in, int fd_out)
{
	char	*cmd;

	cmd = data->args_exec->tab_args[0];
	if (launch_builtin(data, cmd))
	{
		if (fd_in != -1)
			close(fd_in);
		if (fd_out != -1)
			close(fd_out);
		return (1);
	}
	return (0);
}
