#include "../../inc/minishell.h"

void	ft_exec(t_args_exec args_exec)
{
	if (execve(args_exec.path_cmd, args_exec.tab_args, \
		args_exec.path) == -1)
		ft_error(ERR_PERROR, "Execve failed", NULL);
}

void	fill_pipes(t_exec_data *data, int *pipes, int ind_cmd)
{
	static int	mem_l_pipe = 0;
	static int	mem_r_pipe = 2;
	int			temp;

	if (ind_cmd == 0 || ind_cmd == data->n_cmds - 1)
	{
		data->l_pipe = pipes + mem_l_pipe;
		data->r_pipe = pipes;
	}
	else
	{
		data->l_pipe = pipes + mem_l_pipe;
		data->r_pipe = pipes + mem_r_pipe;
		temp = mem_l_pipe;
		mem_l_pipe = mem_r_pipe;
		mem_r_pipe = temp;
	}
}

void	ft_close_pipes(int	*pipes, int dont_close)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (i != dont_close)
			if (close(pipes[i]) == -1)
				ft_error(ERR_PERROR, "Close error", pipes);
		i++;
	}
	ft_free(pipes);
}

void	exe_one_cmd(t_exec_data *data)
{
	int		fd_in;
	int		fd_out;

	data->args_exec->path_cmd = get_path_cmd(data, data->tab_parse[0].tab_args[0]);
	data->args_exec->tab_args = data->tab_parse[0].tab_args;
	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	if (data->tab_parse[0].infile[0])
	{
		fd_in = open(data->tab_parse[0].infile[0], O_RDONLY);
		if (fd_in == -1)
		{
			if (access(data->tab_parse[0].infile[0], F_OK) == -1)
				ft_error(ERR_NO_FILE, data->tab_parse[0].infile[0], data->pipes);
			else if (access(data->tab_parse[0].infile[0], R_OK) == -1)
				ft_error(ERR_PERM_DENIED, data->tab_parse[0].infile[0], data->pipes);
			else 
				ft_error(ERR_PERROR, "Open failed", data->pipes);
		}
	}
	if (data->tab_parse[0].outfile[0])
	{
		if (!ft_strncmp(data->tab_parse[0].outredir[0], ">>", 2))
			fd_out = open(data->tab_parse[0].outfile[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd_out = open(data->tab_parse[0].outfile[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out == -1)
		{
			if (access(data->tab_parse[0].outfile[0], W_OK) == -1)
				ft_error(ERR_PERM_DENIED, data->tab_parse[0].outfile[0], data->pipes);
			else
				ft_error(ERR_PERROR, "Open failed", data->pipes);
		}
	}
	if (data->pipes)
		ft_close_pipes(data->pipes, -1);
	ft_exec(*data->args_exec);
}

int	ft_fork(t_exec_data *data)
{
	int		i;
	pid_t	*childs;
	
	if (data->n_cmds == 1)
		exe_one_cmd(data);
	childs = ft_malloc(sizeof(pid_t) * data->n_cmds);
	if (!childs)
		ft_error(ERR_MALLOC, NULL, NULL);
	i = -1;
	while (++i < data->n_cmds)
	{
		fill_pipes(data, data->pipes, i);
		childs[i] = fork();
		if (childs[i] < 0)
			ft_error(ERR_PERROR, "Fork failed", data->pipes);
		if (childs[i] == 0)
			ft_child(data, i);
	}
	data->childs = childs;
	ft_close_pipes(data->pipes, -1);
	return (ft_wait(data));
}

//TODO :
//gestion d erreur
//regarder d abord si je trouve la commande demandee dans le repertoire courant avant de fouiller le PATH
//cas special si une seule commande a executer (executer dans le parent et non le child)
//heredocs
//pas besoin de gerer les = sans export
//empecher qu'on puisse mettre des arguments a env en mettant un message d'erreur
//executer les builtins au lieu de les chercher dans le path

/*
int	main(int ac, char **av, char *envp[])
{
	t_args_exec	*args_exec;
	t_exec_data	data;

	ft_garbage_collector(INIT, NULL);
	args_exec = init_args_exec();
	data.n_cmds = 4;
	data.args_exec = args_exec;
	set_inoutfies(&data);
	set_redirs(&data);
	ft_fork(&data);
	ft_garbage_collector(END, NULL);
}
*/