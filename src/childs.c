#include "../inc/minishell.h"

static void	set_fds_inout(int *fd_in, int *fd_out, int ind_cmd, \
	t_exec_data *exec_data)
{
	if (ind_cmd == 0)
		*fd_out = exec_data->pipe_fds[ind_cmd + 1];
	else if (ind_cmd == exec_data->n_cmds - 1)
		*fd_in = exec_data->pipe_fds[ind_cmd];
	else
	{
		*fd_in = exec_data->pipe_fds[ind_cmd - 1];
		*fd_out = exec_data->pipe_fds[ind_cmd + 2];
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
	//fprintf(stderr, "fd_in : %d\n", fd_in);
	//fprintf(stderr, "fd_out : %d\n", fd_out);
	if (fd_in != STDIN_FILENO)
		dup2(fd_in, STDIN_FILENO);
	if (fd_out != STDOUT_FILENO)
		dup2(fd_out, STDOUT_FILENO);
	if (ind_cmd == 0)
		close(exec_data->pipe_fds[ind_cmd]);
	else if (ind_cmd == exec_data->n_cmds - 1)
		close(exec_data->pipe_fds[ind_cmd + 1]);
	else
	{
		close(exec_data->pipe_fds[ind_cmd]);
		close(exec_data->pipe_fds[ind_cmd + 1]);
	}
	ft_exec(*exec_data->args_exec, ind_cmd);
}