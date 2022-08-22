#include "../inc/minishell.h"

void	create_outfile(t_exec_data *data, int ind_cmd)
{
	int	outfile;

	outfile = open(data->outfile[ind_cmd], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile == -1)
	{
		if (access(data->outfile[ind_cmd], W_OK) == -1)
			ft_error(ERR_PERM_DENIED, data->outfile[ind_cmd]);
		else
			ft_error(ERR_OPEN, data->outfile[ind_cmd]);
	}
	close(data->r_pipe[1]);
	data->r_pipe[1] = outfile;
}

void	open_infile(t_exec_data *data, int ind_cmd)
{
	int	infile;

	infile = open(data->infile[ind_cmd], O_RDONLY);
	if (infile == -1)
	{
		if (access(data->infile[ind_cmd], F_OK) == -1)
			ft_error(ERR_NO_FILE, data->infile[ind_cmd]);
		else if (access(data->infile[ind_cmd], R_OK) == -1)
			ft_error(ERR_PERM_DENIED, data->infile[ind_cmd]);
		else 
			ft_error(ERR_OPEN, data->infile[ind_cmd]);
	}
	close(data->l_pipe[0]);
	data->l_pipe[0] = infile;
}

static void	set_fds_inout(int *fd_in, int *fd_out, int ind_cmd, \
	t_exec_data *exec_data)
{
	if (exec_data->outfile[ind_cmd])
		create_outfile(exec_data, ind_cmd);
	if (exec_data->infile[ind_cmd])
		open_infile(exec_data, ind_cmd);
	if (ind_cmd == 0)
	{
		if (exec_data->infile[ind_cmd])
			*fd_in = exec_data->l_pipe[0];
		*fd_out = exec_data->r_pipe[1];
	}
	else if (ind_cmd == exec_data->n_cmds - 1)
	{
		if (exec_data->outfile[ind_cmd])
			*fd_out = exec_data->r_pipe[1];
		*fd_in = exec_data->l_pipe[0];
	}
	else
	{
		*fd_in = exec_data->l_pipe[0];
		*fd_out = exec_data->r_pipe[1];
	}
}

static void	close_end_pipe(t_exec_data *exec_data, int ind_cmd)
{
	if (ind_cmd == 0)
		close(exec_data->r_pipe[0]);
	else if (ind_cmd == exec_data->n_cmds - 1)
		close(exec_data->l_pipe[1]);
	else
	{
		close(exec_data->l_pipe[1]);
		close(exec_data->r_pipe[0]);
	}
}

void	ft_child(t_exec_data *exec_data, int ind_cmd)
{
	int		fd_in;
	int		fd_out;
	char	*path_cmd;

	path_cmd = get_path_cmd(exec_data->args_exec->path, \
		exec_data->args_exec->tab_args[ind_cmd][0]);
	exec_data->args_exec->path_cmd = path_cmd;
	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	set_fds_inout(&fd_in, &fd_out, ind_cmd, exec_data);
	if (fd_in != STDIN_FILENO)
		dup2(fd_in, STDIN_FILENO);
	if (fd_out != STDOUT_FILENO)
		dup2(fd_out, STDOUT_FILENO);
	close_end_pipe(exec_data, ind_cmd);
	ft_exec(*exec_data->args_exec, ind_cmd);
}