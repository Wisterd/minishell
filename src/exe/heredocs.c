#include "../../inc/minishell.h"

static char	*create_temp_file_name()
{
	int			available;
	char		*file_name;
	long int	num;

	available = 0;
	num = 0;
	file_name = NULL;
	while (available == 0 && num <= INT_MAX)
	{
		file_name = ft_itoa(num);
		available = access(file_name, F_OK);
		num++;
	}
	if (num == INT_MAX && available == 0)
		ft_error(ERR_NO_FILE, "Create temp file", NULL);
	return (file_name);
}

static void	write_temp_file(t_exec_data *data, int fd, char *here_eof)
{
	char	*prompt;

	prompt = NULL;
	while (ft_strcmp(prompt, here_eof))
	{
		prompt = readline(">");
		if (!prompt)
		{
			if (close(fd) == -1)
				ft_error(ERR_PERROR, "Close failed", NULL);
			return ;
		}
		if (write(fd, prompt, ft_strlen(prompt)) == -1)
			ft_error(ERR_PERROR, "Write failed", NULL);
	}
	if (close(fd) == -1)
		ft_error(ERR_PERROR, "Close failed", NULL);
	ft_garbage_collector(END, NULL);
	ft_garbage_collector_perm(END, NULL);
	exit(0);
}

static void	fork_temp_file(t_exec_data *data, int ind_cmd)
{
	int		fd_here;
	char	*file_name;
	pid_t	child;
	int		status;

	file_name = create_temp_file_name();
	fd_here = open(file_name, O_WRONLY);
	if (fd_here == -1)
		ft_error(ERR_PERROR, "Open failed", NULL);
	child = fork();
	if (child < 0)
		ft_error(ERR_PERROR, "Fork failed", NULL);
	if (child == 0)
		write_temp_file(data, fd_here, data->tab_parse[ind_cmd].infile);
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		g_exit_stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_stat = WTERMSIG(128 + status);
	ft_free(data->tab_parse[ind_cmd].infile);
	data->tab_parse[ind_cmd].infile = file_name;
}

void	look_for_heredocs(t_exec_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd)
	{
		if (ft_strcmp(data->tab_parse[i].inredir, "<<") == 0)
			fork_temp_file(data, i);
		i++;
	}
}