#include "../../inc/minishell.h"

int g_exit_stat = 0;

void	ft_exit_error(int exit_stat)
{
	ft_garbage_collector(END, NULL);
	ft_garbage_collector_perm(END, NULL);
	exit(exit_stat);
}

void	ft_error(int error_code, char *to_print, int *pipes)
{
	int		exit_stat;
	char	*error_msg;

	if (error_code == ERR_NOT_FOUND)
	{
		exit_stat = 127;
		error_msg = ft_strjoin(to_print, ": command not found\n");
	}
	if (error_code == ERR_PERM_DENIED)
	{
		exit_stat = 126;
		error_msg = ft_strjoin(to_print, ": Permission denied\n");
	}
	if (error_code == ERR_NO_FILE)
	{
		exit_stat = 127;
		error_msg = ft_strjoin(to_print, ": No such file or directory\n");
	}
	if (error_code == ERR_MALLOC)
	{
		exit_stat = 1;
		error_msg = ft_strjoin(to_print, "Malloc error\n");
	}
	if (error_code == ERR_PERROR)
	{
		exit_stat = 1;
		perror(to_print);
	}
	if (pipes)
		ft_close_pipes(pipes, -1);
	write(2, error_msg, ft_strlen(error_msg));
	ft_exit_error(exit_stat);
}