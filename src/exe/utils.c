#include "../../inc/minishell.h"

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

int	ft_wait(t_exec_data *data)
{
	int		status;
	int		res;
	ssize_t	i;

	status = 0;
	res = 0;
	i = 0;
	while (i < data->n_cmds)
	{
		waitpid(data->childs[i], &status, 0);
		if (WIFEXITED(status))
			res = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			res = WTERMSIG(128 + status);
		i++;
	}
	return (res);
}

char	*ft_getcwd(t_exec_data *data)
{
	char	*str_cwd;

	str_cwd = ft_malloc(sizeof(char) * PATH_MAX);
	if (!getcwd(str_cwd, sizeof(char) * PATH_MAX))
		ft_error(ERR_PERROR, "Getcwd failed", data->pipes);
	return (str_cwd);
}

void	ft_exit_error(void)
{
	ft_garbage_collector(END, NULL);
	exit(1);
}