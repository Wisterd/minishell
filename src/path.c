#include "../inc/minishell.h"

static char	*search_path_cmd(char **split_path, char *cmd, int *path_state)
{
	int		i;
	char	*path_cmd;

	i = 0;
	path_cmd = NULL;
	while (split_path[i] && *path_state != ACCESSIBLE)
	{
		if (path_cmd)
			ft_free(path_cmd);
		path_cmd = ft_strjoin(split_path[i], "/");
		path_cmd = ft_strjoin_free(path_cmd, cmd);
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

static char	*direct_path(char *cmd)
{
	char	*path_cmd;

	path_cmd = ft_strdup(cmd);
	if (!path_cmd)
		ft_error(ERR_MALLOC, NULL);
	if (access(path_cmd, F_OK == -1))
		ft_error(ERR_NO_FILE, path_cmd);
	if (access(path_cmd, X_OK) == -1)
		ft_error(ERR_PERM_DENIED, path_cmd);
	return (path_cmd);
}

char	*get_path_cmd(char **split_path, char *cmd)
{
	char	*path_cmd;
	int		path_state;

	path_state = 0;
	if (ft_strlen(cmd) == 0)
		ft_error(ERR_NOT_FOUND, "''");
	if (ft_strchr(cmd, '/') != 0)
		path_cmd = direct_path(cmd);
	else
	{
		path_cmd = search_path_cmd(split_path, cmd, &path_state);
		if (path_state == ACCESSIBLE)
			return (path_cmd);
		if (path_state == EXISTS)
			ft_error(ERR_PERM_DENIED, cmd);
		if (path_state == 0)
			ft_error(ERR_NOT_FOUND, cmd);
	}
	return (path_cmd);
}