#include "../inc/minishell.h"

/*
t_args_exec	init_args_exec(char **av, char *envp[])
{
	
}
*/

void	ft_exec(char *cmd, char **args, char **path_cmd)
{
	execve(cmd, args, path_cmd);
}

int	*ft_pipe(int n_pipe)
{
	int	i;
	int	*pipe_fds;

	i = 0;
	pipe_fds = ft_malloc(sizeof(int) * (2 * n_pipe + 1));
	while (i < n_pipe)
	{
		pipe(pipe_fds + 2 * i * sizeof(int));
		//differentes erreurs intressantes de pipe
		i++;
	}
	pipe_fds[2 * n_pipe] = -2;
	return (pipe_fds);
}

int	main(int ac, char **av, char *envp[])
{
	(void)	ac;
	(void)	av;
	(void)	envp;
	int	*pipe_fds;

	garbage_collector(INIT, NULL);
	pipe_fds = ft_pipe(3);
	garbage_collector(END, NULL);
}