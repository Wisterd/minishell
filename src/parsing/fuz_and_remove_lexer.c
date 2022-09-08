/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuz_and_remove_lexer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:04:37 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/08 19:02:25 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	near_mot(t_lexer **deb_lexer)
{
	t_lexer	*tmp_lexer;

	tmp_lexer = *deb_lexer;
	while (tmp_lexer && tmp_lexer->next)
	{
		if (tmp_lexer->type == MOT && tmp_lexer->next->type == MOT)
			return (1);
		tmp_lexer = tmp_lexer->next;
	}
	return (0);
}

t_lexer	*change_in_quote(t_lexer *tmp_lexer, char *str)
{
	while (tmp_lexer && ft_strncmp(tmp_lexer->contenu, str, 2))
	{
		if (!ft_strncmp(tmp_lexer->contenu, "\"", 1))
			tmp_lexer->type = CMD;
		else if (!ft_strncmp(tmp_lexer->contenu, "'", 1) || !ft_strncmp(tmp_lexer->contenu, " ", 1))
			tmp_lexer->type = CMD;
		else if (!ft_strncmp(str, "\"", 2) \
		&& !ft_strncmp(tmp_lexer->contenu, "$", 2))
			tmp_lexer->type = DOLLAR;
		else
			tmp_lexer->type = MOT;
		tmp_lexer = tmp_lexer->next;
		if (!tmp_lexer)
			return (NULL);
	}
	return (tmp_lexer);
}

int	in_quote(t_lexer **deb_lexer)
{
	char	*str;
	t_lexer	*tmp_lexer;

	tmp_lexer = *deb_lexer;
	while (tmp_lexer)
	{
		if (tmp_lexer->type == QUOTE)
		{
			str = tmp_lexer->contenu;
			if (!tmp_lexer->next)
				return (1);
			tmp_lexer = tmp_lexer->next;
			if(!strncmp(tmp_lexer->contenu, str , 1))
			{
				ft_free(tmp_lexer->contenu);
				tmp_lexer->contenu = ft_strdup("");
				tmp_lexer->type = MOT;
				free_one_element(deb_lexer, tmp_lexer->pre);
			}
			else if (!change_in_quote(tmp_lexer, str))
				return (1);
			else
				tmp_lexer = change_in_quote(tmp_lexer, str);
		}
		tmp_lexer = tmp_lexer->next;
	}
	return (0);
}

int	have_type(t_lexer **deb_lexer, int type)
{
	t_lexer	*tmp_lexer;

	tmp_lexer = *deb_lexer;
	while (tmp_lexer)
	{
		if (tmp_lexer->type == type)
			return (1);
		tmp_lexer = tmp_lexer->next;
	}
	return (0);
}

void	remove_type(t_lexer **deb_lexer, int type)
{
	t_lexer	*tmp_lexer;
	t_lexer	*next;

	tmp_lexer = *deb_lexer;
	while (tmp_lexer)
	{
		next = tmp_lexer->next;
		if (tmp_lexer->type == type)
			free_one_element(deb_lexer, tmp_lexer);
		tmp_lexer = next;
	}
}
