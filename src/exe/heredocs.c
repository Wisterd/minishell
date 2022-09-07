/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:15:49 by mvue              #+#    #+#             */
/*   Updated: 2022/09/07 17:34:47 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*create_temp_file_name(void)
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

static void	write_temp_file(char *to_write, char *file_name)
{
	int		fd_here;

	fd_here = open(file_name, O_CREAT | O_WRONLY, 0644);
	if (fd_here == -1)
		ft_error(ERR_PERROR, "Open failed", NULL);
	write(fd_here, to_write, ft_strlen(to_write));
	if (close(fd_here) == -1)
		ft_error(ERR_PERROR, "Close failed", NULL);
}

static void	readline_temp_file(char *file_name, char *here_eof)
{
	char	*prompt;
	char	*line;
	char	*to_write;

	prompt = NULL;
	to_write = ft_strdup("");
	if (!to_write)
		ft_error(ERR_MALLOC, NULL, NULL);
	while (1)
	{
		if (prompt)
			free(prompt);
		prompt = readline("> ");
		if (!ft_strcmp(prompt, here_eof) || !prompt)
		{
			write_temp_file(to_write, file_name);
			break ;
		}
		line = ft_strjoin_free(prompt, "\n");
		prompt = NULL;
		if (!line)
			ft_error(ERR_MALLOC, NULL, NULL);
		to_write = ft_strjoin_2free(to_write, line);
		if (!to_write)
			ft_error(ERR_MALLOC, NULL, NULL);
	}
	ft_garbage_collector(END, NULL);
	ft_garbage_collector_perm(END, NULL);
	exit(0);
}

static void	fork_temp_file(t_exec_data *data, int ind_cmd, int ind_redir)
{
	char	*file_name;
	pid_t	child;
	int		status;

	file_name = create_temp_file_name();
	child = fork();
	if (child < 0)
		ft_error(ERR_PERROR, "Fork failed", NULL);
	if (child == 0)
		readline_temp_file(file_name, \
			data->tab_parse[ind_cmd].infile[ind_redir]);
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		g_exit_stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_stat = WTERMSIG(128 + status);
	ft_free(data->tab_parse[ind_cmd].infile[ind_redir]);
	data->tab_parse[ind_cmd].infile[ind_redir] = file_name;
}

void	look_for_heredocs(t_exec_data *data)
{
	int	ind_cmd;
	int	ind_redir;

	ind_cmd = 0;
	while (ind_cmd < data->n_cmds)
	{
		ind_redir = 0;
		while (data->tab_parse[ind_cmd].inredir[ind_redir])
		{
			if (ft_strcmp(data->tab_parse[ind_cmd].inredir[ind_redir], \
				"<<") == 0)
				fork_temp_file(data, ind_cmd, ind_redir);
			ind_redir++;
		}
		ind_cmd++;
	}
}

/*
int	main(void)
{
	int		fd_here;
	char	*file_name;

	file_name = create_temp_file_name();
	fd_here = open(file_name, O_WRONLY);
	if (fd_here == -1)
		ft_error(ERR_PERROR, "Open failed", NULL);
}
*/