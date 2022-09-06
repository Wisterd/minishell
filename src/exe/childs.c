#include "../../inc/minishell.h"

void	create_outfile(t_exec_data *data, int ind_cmd)
{
	int		outfile;
	int		ind_last;
	char	*outname;
	
	create_all_out(data, data->tab_parse[ind_cmd].outfile);
	ind_last = get_ind_last_redir(data->tab_parse[ind_cmd].outredir);
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
	
	open_all_in(data, data->tab_parse[ind_cmd].infile);
	ind_last = get_ind_last_redir(data->tab_parse[ind_cmd].inredir);
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

void	ft_child(t_exec_data *data)
{
	int		fd_in;
	int		fd_out;
	char	*path_cmd;

	data->args_exec->tab_args = data->tab_parse[data->ind_cmd].tab_args;
	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	set_fds_inout(&fd_in, &fd_out, data->ind_cmd, data);
	if (fd_in != STDIN_FILENO)
		if (dup2(fd_in, STDIN_FILENO) == -1)
			ft_error(ERR_PERROR, "Dup2 failed", data->pipes);
	if (fd_out != STDOUT_FILENO)
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			ft_error(ERR_PERROR, "Dup2 failed", data->pipes);
	ft_close_pipes(data->pipes, -1);
	if (is_builtin(data->args_exec->tab_args[0]))
	{
		exe_builtin(data);
		ft_garbage_collector(END, NULL);
		ft_garbage_collector_perm(END, NULL);
		close(0);
		close(1);
		exit (g_exit_stat);
	}
	if (!data->tab_parse[data->ind_cmd].tab_args[0])
	{
		close(0);
		close(1);
		ft_garbage_collector(END, NULL);
		ft_garbage_collector_perm(END, NULL);
		exit(0);
	}
	path_cmd = get_path_cmd(data, \
		data->args_exec->tab_args[0]);
	data->args_exec->path_cmd = path_cmd;
	data->args_exec->tab_env = ft_get_total_env(data);
	ft_exec(*data->args_exec);
}