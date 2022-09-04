#include "../../inc/minishell.h"

int	get_ind_last_redir(char **redirs)
{
	int	i;

	i = 0;
	while (redirs[i])
		i++;
	i--;
	return (i);
}

void	create_all_out(t_exec_data *data, char **outfiles)
{
	int	i;
	int	outfile;

	i = 0;
	if (!outfiles[1])
		return ;
	while (outfiles[i + 1])
	{
		outfile = open(outfiles[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (outfile == -1)
		{
			if (access(outfiles[i], W_OK) == -1)
				ft_error(ERR_PERM_DENIED, outfiles[i], data->pipes);
			else
				ft_error(ERR_PERROR, "Open failed", data->pipes);
		}
		if (close(outfile) == -1)
			ft_error(ERR_PERROR, "Close failed", data->pipes);
		i++;
	}
}

void	open_all_in(t_exec_data *data, char **infiles)
{
	int	i;
	int	infile;
	i = 0;
	if (!infiles[1])
		return ;
	while (infiles[i])
	{
		infile = open(infiles[i], O_RDONLY);
		if (infile == -1)
		{
			if (access(infiles[i], F_OK) == -1)
				ft_error(ERR_NO_FILE, infiles[i], data->pipes);
			else if (access(infiles[i], R_OK) == -1)
				ft_error(ERR_PERM_DENIED, infiles[i], data->pipes);
			else 
				ft_error(ERR_PERROR, "Open failed", data->pipes);
		}
		if (close(infile) == -1)
			ft_error(ERR_PERROR, "Close failed", data->pipes);
		i++;
	}
}

void	unlink_heredocs(t_exec_data *data)
{
	int	ind_cmd;
	int	ind_redir;

	ind_cmd = 0;
	while (ind_cmd < data->n_cmds)
	{
		ind_redir = 0;
		while (data->tab_parse[ind_cmd].inredir[ind_redir])
		{
			if (ft_strcmp(data->tab_parse[ind_cmd].inredir[ind_redir], "<<") == 0)
				if (unlink(data->tab_parse[ind_cmd].infile[ind_redir]) == -1)
					ft_error(ERR_PERROR, "Unlink failed", NULL);
			ind_redir++;
		}
		ind_cmd++;
	}
}
