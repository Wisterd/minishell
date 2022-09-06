#include "../../inc/minishell.h"

static char	*search_path_cmd(t_exec_data *data, char *cmd, int *path_state)
{
	int		i;
	char	*path_cmd;
	char	**path;

	i = 0;
	path_cmd = NULL;
	path = ft_split(ft_getenv("PATH", data), ':');
	while (path[i] && *path_state != ACCESSIBLE)
	{
		if (path_cmd)
			ft_free(path_cmd);
		path_cmd = ft_strjoin(path[i], "/");
		if (!path_cmd)
			ft_error(ERR_MALLOC, NULL, data);
		path_cmd = ft_strjoin_1free(path_cmd, cmd);
		if (!path_cmd)
			ft_error(ERR_MALLOC, NULL, data);
		if (access(path_cmd, F_OK) != -1)
		{
			*path_state = EXISTS;
			if (access(path_cmd, X_OK) != -1)
				*path_state = ACCESSIBLE;
		}
		i++;
	}
	return (path_cmd);
}

static char	*direct_path(t_exec_data *data, char *cmd)
{
	char	*path_cmd;

	path_cmd = ft_strdup(cmd);
	if (!path_cmd)
		ft_error(ERR_MALLOC, NULL, data);
	if (access(path_cmd, F_OK == -1))
		ft_error(ERR_NO_FILE, path_cmd, data);
	if (access(path_cmd, X_OK) == -1)
		ft_error(ERR_PERM_DENIED, path_cmd, data);
	return (path_cmd);
}

char	*get_path_cmd(t_exec_data *data, char *cmd)
{
	char	*path_cmd;
	int		path_state;

	path_state = 0;
	if (ft_strlen(cmd) == 0)
		ft_error(ERR_NOT_FOUND, "''", data);
	if (ft_strchr(cmd, '/') != 0)
		path_cmd = direct_path(data, cmd);
	else
	{
		if (!ft_getenv("PATH", data))
		{
			path_cmd = direct_path(data, cmd);
			return (path_cmd);
		}
		path_cmd = search_path_cmd(data, cmd, &path_state);
		if (path_state == ACCESSIBLE)
			return (path_cmd);
		if (path_state == EXISTS)
			ft_error(ERR_PERM_DENIED, cmd, data);
		if (path_state == 0)
			ft_error(ERR_NOT_FOUND, cmd, data);
	}
	return (path_cmd);
}