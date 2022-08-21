/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 00:01:00 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/21 03:06:00 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	fuz_lex(t_lexer **deb_lexer, int type)
{
	t_lexer	*new_lexer;
	t_lexer	*tmp_lexer;

	new_lexer = *deb_lexer;
	while (new_lexer && new_lexer->next && ft_strncmp(new_lexer->contenu, "/n", 2))
	{
		if (!ft_strncmp(new_lexer->next->contenu, "'", 1))
		{
			new_lexer->next->type = CMD;
			new_lexer = new_lexer->next;
		}		
		else if (new_lexer->type == type && new_lexer->next->type == type)
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

void	free_one_element(t_lexer **deb_lexer, t_lexer *tmp_lexer)
{
	t_lexer	*to_free;

	to_free = tmp_lexer;
	if (!tmp_lexer->pre)
	{
		tmp_lexer = tmp_lexer->next;
		*deb_lexer = tmp_lexer;
		if (to_free->pre)
			tmp_lexer->pre = NULL;
		free(to_free->contenu);
		free(to_free);
	}
	else
	{
		if (tmp_lexer->next)
		{
			tmp_lexer = tmp_lexer->next;
			tmp_lexer->pre = tmp_lexer->pre->pre;
			if (tmp_lexer->pre)
				tmp_lexer->pre->next = tmp_lexer;
		}
		else
			tmp_lexer->pre->next = NULL;
		free(to_free->contenu);
		free(to_free);
	}
	to_free = NULL;
}
/*
int pull_env(char *str)
{
	char **path;
	int	i;

	i = 0;
	path = ft_split(getenv("PATH"), ':');
	//error_malloc("pull_env split");
	while (path[i])
	{
		path[i] = ft_strjoin_1free(path[i], "/");
		if (!path[i])
			error_malloc("pull_env strjoin num 1");
		path[i] = ft_strjoin_1free(path[i], str);
		if (!path[i])
			error_malloc("pull_env strjoin num 2");
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
	t_lexer	*tmp_lexer;
	int		possible_cmd;

	possible_cmd = 1;
	new_lexer = *deb_lexer;
	while (new_lexer)
	{
		if (new_lexer->type == MOT && possible_cmd)
			if (pull_env(new_lexer->contenu))
			{
				tmp_lexer = new_lexer;
				while (tmp_lexer->pre && tmp_lexer->pre->type == SPC)
					tmp_lexer = tmp_lexer->pre;
				if (tmp_lexer->type == REDIR)
					;
				else
				{
					new_lexer->type = CMD;
					possible_cmd = 0;
				}
			}
		if  (new_lexer->type == PIPE)
			possible_cmd = 1;
		new_lexer = new_lexer->next;
	}
}
*/