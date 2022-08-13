#include "../inc/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	s3 = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + sizeof(char));
	i = -1;
	j = 0;
	if (!s3)
		return (NULL);
	else
	{
		while (s1[++i])
			s3[i] = s1[i];
		while (s2[j])
			s3[i++] = s2[j++];
		s3[i] = '\0';
	}
	ft_free(s1);
	return (s3);
}

/*
t_args_exec	init_args_exec(char *cmds)
{
	t_args_exec	args_exec;
	char		**path_cmds;

	args_exec.path = ft_split(getenv("PATH"), ':');
	path_cmds = ft_malloc(sizeof(char *) * ac - 1);
	return (args_exec);
}
*/

void	ft_exec(char *path_cmd, char **args, char **path)
{
	execve(path_cmd, args, path);
}

int	*init_pipes(int n_pipe)
{
	int	i;
	int	*pipe_fds;

	i = 0;
	pipe_fds = ft_malloc(sizeof(int) * (2 * n_pipe + 1));
	while (i < n_pipe)
	{
		pipe(pipe_fds + 2 * i);
		//differentes erreurs intressantes de pipe
		i++;
	}
	pipe_fds[2 * n_pipe] = -2;
	return (pipe_fds);
}


pid_t	*ft_fork(t_args_exec args_exec, int n_cmds)
{
	int		*pipe_fds;
	int		i;
	pid_t	*childs;
	
	childs = ft_malloc(sizeof(pid_t) * n_cmds);
	pipe_fds = init_pipes(n_cmds - 1);
	i = 0;
	while (i < n_cmds)
	{
		childs[i] = fork();
		if (childs[i] < 0)
			ft_error(ERR_FORK, NULL);
		if (childs[i] == 0)
			ft_child(args_exec, i, pipe_fds);
		i++;
	}
	ft_wait();
	ft_close_pipes();
}

int	main(int ac, char **av)
{
	ft_garbage_collector(INIT, NULL);
	ft_garbage_collector(END, NULL);
}
