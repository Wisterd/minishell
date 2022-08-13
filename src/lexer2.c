/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 00:01:00 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/13 17:22:45 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	fuz_lex(t_lexer **deb_lexer, int type)
{
	t_lexer	*new_lexer;
	t_lexer	*tmp_lexer;

	new_lexer = *deb_lexer;
	while (new_lexer && new_lexer->next)
	{
		if (new_lexer->type == type && new_lexer->next->type == type)
		{
			new_lexer->contenu = ft_strjoin_2free(\
			new_lexer->contenu, new_lexer->next->contenu);
			if (!new_lexer->contenu)
				error_malloc("fuz_lex");
			tmp_lexer = new_lexer->next->next;
			free(new_lexer->next);
			new_lexer->next = tmp_lexer;
			if (tmp_lexer)
				tmp_lexer->pre = new_lexer;
		}
		else if (new_lexer->next)
		{
			if (new_lexer->pre)
				new_lexer->id = new_lexer->pre->id + 1;
			new_lexer = new_lexer->next;
		}
		if (new_lexer->pre)
			new_lexer->id = new_lexer->pre->id + 1;
	}
}

int pull_env(char *str)
{
	char **path;
	int	i;

	i = 0;
	path = ft_split(getenv("PATH"), ':');
	while (path[i])
	{
		path[i] = ft_strjoin_1free(path[i], "/");
		if (!path[i])
			error_malloc("pull_env");
		path[i] = ft_strjoin_1free(path[i], str);
		if (!path[i])
			error_malloc("pull_env");
		if (!access(path[i], F_OK))
		{
			free(path);
			return (1);
		}
		free(path[i]);
		i++;
	}
	free(path);
	return(0);
}

void	word_or_cmd(t_lexer **deb_lexer)
{
	t_lexer	*new_lexer;
	int		possible_cmd;

	possible_cmd = 1;
	new_lexer = *deb_lexer;
	while (new_lexer)
	{
		if (new_lexer->type == MOT && possible_cmd)
			if (pull_env(new_lexer->contenu))
			{
				new_lexer->type = CMD;
				possible_cmd = 0;
			}
		if  (new_lexer->type == PIPE)
			possible_cmd = 1;
		new_lexer = new_lexer->next;
	}
}
