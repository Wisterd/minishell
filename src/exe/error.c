#include "../../inc/minishell.h"

int g_exit_stat = 0;

void	ft_error(int error_code, char *to_print, int *pipes)
{
	char	*error_msg;

	if (error_code == ERR_NOT_FOUND)
	{
		g_exit_stat = 127;
		error_msg = ft_strjoin(to_print, ": command not found\n");
	}
	if (error_code == ERR_PERM_DENIED)
	{
		g_exit_stat = 126;
		error_msg = ft_strjoin(to_print, ": Permission denied\n");
	}
	if (error_code == ERR_NO_FILE)
	{
		g_exit_stat = 127;
		error_msg = ft_strjoin(to_print, ": No such file or directory\n");
	}
	if (error_code == ERR_MALLOC)
	{
		g_exit_stat = 1;
		error_msg = ft_strjoin(to_print, "Malloc error\n");
	}
	if (error_code == ERR_PERROR)
	{
		g_exit_stat = 1;
		perror(to_print);
	}
	if (pipes)
		ft_close_pipes(pipes, -1);
	write(2, error_msg, ft_strlen(error_msg));
	ft_exit_error();
}