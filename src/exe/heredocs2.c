/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:06:58 by mvue              #+#    #+#             */
/*   Updated: 2022/09/12 19:17:03 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_wait_heredocs(pid_t child)
{
	int		status;

	waitpid(child, &status, 0);
	signals();
	if (WIFEXITED(status))
		g_exit_stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_stat = WTERMSIG(128 + status);
}

void	heredoc_joins(char **prompt, char **line, char **to_write)
{
	*line = ft_strjoin_free(*prompt, "\n");
	*prompt = NULL;
	if (!*line)
		ft_error(ERR_MALLOC, NULL, NULL);
	*to_write = ft_strjoin_2free(*to_write, *line);
	if (!*to_write)
		ft_error(ERR_MALLOC, NULL, NULL);
}
