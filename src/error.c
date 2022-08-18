#include "../inc/minishell.h"

int exit_stat = 0;

void	ft_error(int error_code, char *to_print)
{
	if (error_code == ERR_NOT_FOUND)
	{
		exit_stat = 127;
		ft_putstr_fd(to_print, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (error_code == ERR_PERM_DENIED)
	{
		exit_stat = 126;
		ft_putstr_fd(to_print, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	if (error_code == ERR_NO_FILE)
	{
		exit_stat = 127;
		ft_putstr_fd(to_print, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	if (error_code == ERR_MALLOC)
	{
		exit_stat = 1;
		ft_putstr_fd("Malloc error\n", 2);
	}
	if (error_code == ERR_FORK)
	{
		exit_stat = 1;
		ft_putstr_fd("Fork error\n", 2);
	}
	ft_exit();
}