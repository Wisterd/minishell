#include "../../inc/minishell.h"

void	launch_builtin(t_exec_data *data, char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		ft_echo(data->tab_parse[data->ind_cmd].tab_args);
	if (!ft_strcmp(cmd, "env"))
		ft_env(data);
	if (!ft_strcmp(cmd, "unset"))
		ft_unset(data);
}
