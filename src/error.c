#include "../inc/minishell.h"

int exit_stat = 0;

void	ft_error(int error_code, char *to_print)
{
	if (error_code == 1)
	{
		exit_stat = 127;
		ft_putstr_fd(to_print, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (error_code == 2)
	{
		exit_stat = 126;
		ft_putstr_fd(to_print, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	if (error_code == 3)
	{
		exit_stat = 127;
		ft_putstr_fd(to_print, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	ft_garbage_collector(END, NULL);
	exit(1);
}