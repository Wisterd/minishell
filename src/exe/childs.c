#include "../../inc/minishell.h"

int	get_ind_last_redir(char **redirs)
{
	int	i;

	i = 0;
	while (redirs[i])
		i++;
	return (i);
}

void	create_outfile(t_exec_data *data, int ind_cmd)
{
	int		outfile;
	int		ind_last;
	char	*outname;
	
	ind_last = get_ind_last_redir(data->tab_parse->outredir);
	outname = data->tab_parse[ind_cmd].outfile[ind_last];
	if (!ft_strncmp(data->tab_parse[ind_cmd].outredir[ind_last], ">>", 2))
		outfile = open(outname, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		outfile = open(outname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile == -1)
	{
		if (access(outname, W_OK) == -1)
			ft_error(ERR_PERM_DENIED, outname, data->pipes);
		else
			ft_error(ERR_PERROR, "Open failed", data->pipes);
	}
	if (close(data->r_pipe[1]) == -1)
		ft_error(ERR_PERROR, "Close failed", data->pipes);
	data->r_pipe[1] = outfile;
}

void	open_infile(t_exec_data *data, int ind_cmd)
{
	int		infile;
	int		ind_last;
	char	*inname;
	
	ind_last = get_ind_last_redir(data->tab_parse->inredir);
	inname = data->tab_parse[ind_cmd].infile[ind_last];
	infile = open(inname, O_RDONLY);
	if (infile == -1)
	{
		if (access(inname, F_OK) == -1)
			ft_error(ERR_NO_FILE, inname, data->pipes);
		else if (access(inname, R_OK) == -1)
			ft_error(ERR_PERM_DENIED, inname, data->pipes);
		else 
			ft_error(ERR_PERROR, "Open failed", data->pipes);
	}
	if (close(data->l_pipe[0]) == -1)
		ft_error(ERR_PERROR, "Close failed", data->pipes);
	data->l_pipe[0] = infile;
}

static void	set_fds_inout(int *fd_in, int *fd_out, int ind_cmd, \
	t_exec_data *exec_data)
{
	if (exec_data->tab_parse[ind_cmd].outfile[0])
		create_outfile(exec_data, ind_cmd);
	if (exec_data->tab_parse[ind_cmd].infile[0])
		open_infile(exec_data, ind_cmd);
	if (ind_cmd == 0)
	{
		if (exec_data->tab_parse[ind_cmd].infile[0])
			*fd_in = exec_data->l_pipe[0];
		*fd_out = exec_data->r_pipe[1];
	}
	else if (ind_cmd == exec_data->n_cmds - 1)
	{
		if (exec_data->tab_parse[ind_cmd].outfile[0])
			*fd_out = exec_data->r_pipe[1];
		*fd_in = exec_data->l_pipe[0];
	}
	else
	{
		*fd_in = exec_data->l_pipe[0];
		*fd_out = exec_data->r_pipe[1];
	}
}

void	ft_child(t_exec_data *exec_data, int ind_cmd)
{
	int		fd_in;
	int		fd_out;
	char	*path_cmd;

	exec_data->args_exec->tab_args = exec_data->tab_parse[ind_cmd].tab_args;
	path_cmd = get_path_cmd(exec_data, \
		exec_data->args_exec->tab_args[0]);
	exec_data->args_exec->path_cmd = path_cmd;
	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	set_fds_inout(&fd_in, &fd_out, ind_cmd, exec_data);
	if (fd_in != STDIN_FILENO)
		if (dup2(fd_in, STDIN_FILENO) == -1)
			ft_error(ERR_PERROR, "Dup2 failed", exec_data->pipes);
	if (fd_out != STDOUT_FILENO)
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			ft_error(ERR_PERROR, "Dup2 failed", exec_data->pipes);
	ft_close_pipes(exec_data->pipes, -1);
	ft_exec(*exec_data->args_exec);
}