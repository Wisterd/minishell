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
	free(s1);
	return (s3);
}

char	*search_path_cmd(char **split_path, char *cmd, int *path_state)
{
	int		i;
	char	*path_cmd;

	i = 0;
	path_cmd = NULL;
	while (split_path[i] && *path_state != ACCESSIBLE)
	{
		if (path_cmd)
			free(path_cmd);
		path_cmd = ft_strjoin(split_path[i], '/');
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

char	*direct_path(char *cmd, int *path_state)
{

}

char	*get_path_cmd(char **split_path, char *cmd)
{
	char	*path_cmd;
	int		path_state;

	path_state = 0;
	if (ft_strchr(cmd, '/') != 0)
	{
		path_cmd = direct_path(cmd, &path_state);
		if (path_state != EXISTS)
	}
	else
	{
		path_cmd = search_path_cmd(split_path, cmd, &path_state);
	}
	return (path_cmd);
}
t_args_exec	init_args_exec(int ac, char **av)
{
	t_args_exec	args_exec;
	char		**path_cmds;

	args_exec.path = ft_split(getenv("PATH"), ':');
	path_cmds = ft_malloc(sizeof(char *) * ac - 1);
	return (args_exec);
}

void	ft_exec(char *path_cmd, char **args, char **path)
{
	execve(path_cmd, args, path);
}

pid_t	*ft_fork(t_args_exec args_exec)
{
	int	i;

	i = 0;
	while ()
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

int	main(int ac, char **av)
{
	int		*pipe_fds;
	int		n_pipes;
	int		i;


	n_pipes = 5;
	ft_garbage_collector(INIT, NULL);
	init_args_exec(ac, av);
	pipe_fds = init_pipes(n_pipes);
	i = 0;
	while(pipe_fds[i] != -2)
	{
		printf("%d\n", pipe_fds[i]);
		i++;
	}
	ft_garbage_collector(END, NULL);
}