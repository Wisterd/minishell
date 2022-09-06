#include "../../inc/minishell.h"

static void	one_cmd_in(t_exec_data *data)
{
	int	fd_in;
	int	ind_last;

	fd_in = STDIN_FILENO;
	open_all_in(data, data->tab_parse[0].infile);
	ind_last = get_ind_last_redir(data->tab_parse[0].inredir);
	if (data->tab_parse[0].infile[0])
	{
		fd_in = open(data->tab_parse[0].infile[ind_last], O_RDONLY);
		if (fd_in == -1)
		{
			if (access(data->tab_parse[0].infile[ind_last], F_OK) == -1)
				ft_error(ERR_NO_FILE, data->tab_parse[0].infile[ind_last], data);
			else if (access(data->tab_parse[0].infile[ind_last], R_OK) == -1)
				ft_error(ERR_PERM_DENIED, data->tab_parse[0].infile[ind_last], data);
			else 
				ft_error(ERR_PERROR, "Open failed", data);
		}
		if (dup2(fd_in, STDIN_FILENO) == -1)
			ft_error(ERR_PERROR, "Dup2 failed", data);
		close(fd_in);
	}
}

static void	one_cmd_out(t_exec_data *data)
{
	int	fd_out;
	int	ind_last;

	fd_out = STDOUT_FILENO;
	create_all_out(data, data->tab_parse[0].outfile);
	ind_last = get_ind_last_redir(data->tab_parse[0].outredir);
	if (data->tab_parse[0].outfile[0])
	{
		if (!ft_strncmp(data->tab_parse[0].outredir[ind_last], ">>", 2))
			fd_out = open(data->tab_parse[0].outfile[ind_last], O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd_out = open(data->tab_parse[0].outfile[ind_last], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out == -1)
		{
			if (access(data->tab_parse[0].outfile[0], W_OK) == -1)
				ft_error(ERR_PERM_DENIED, data->tab_parse[0].outfile[ind_last], data);
			else
				ft_error(ERR_PERROR, "Open failed", data);
		}
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			ft_error(ERR_PERROR, "Dup2 failed", data);
		close(fd_out);
	}
}

static void	child_one_cmd(t_exec_data *data)
{
	if (*data->tab_parse[0].infile)
		one_cmd_in(data);
	if (*data->tab_parse[0].outfile)
		one_cmd_out(data);
	if (data->pipes)
		ft_close_pipes(data);
	if (!data->args_exec[0].tab_args[0])
	{
		close(0);
		close(1);
		ft_garbage_collector(END, NULL);
		ft_garbage_collector_perm(END, NULL);
		exit(0);
	}
	else
	{
		data->args_exec->path_cmd = get_path_cmd(data, data->tab_parse[0].tab_args[0]);
		data->args_exec->tab_env = ft_get_total_env(data);
		ft_exec(*data->args_exec);
	}
}

int	exe_one_cmd(t_exec_data *data)
{
	pid_t	child;
	int		status;

	status = 0;
	child = fork();
	if (child < 0)
		ft_error(ERR_PERROR, "Fork failed", data);
	if (child == 0)
		child_one_cmd(data);
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(128 + status));
	return (status);
}