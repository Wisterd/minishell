/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 00:01:00 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/08 19:40:04 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_lexer	**create_deb_lexer(void)
{
	t_lexer	**deb_lexer;

	deb_lexer = ft_malloc(sizeof(*deb_lexer));
	error_malloc("lexing", deb_lexer);
	*deb_lexer = NULL;
	return (deb_lexer);
}

void	fuz_lex(t_lexer **deb_lexer, int type)
{
	t_lexer	*new_lexer;
	t_lexer	*tmp_lexer;

	new_lexer = *deb_lexer;
	while (new_lexer && new_lexer->next && \
	ft_strncmp(new_lexer->contenu, "/n", 2))
	{
		if (new_lexer->type == type && new_lexer->next->type == type)
		{
			new_lexer->contenu = ft_strjoin_2free(\
			new_lexer->contenu, new_lexer->next->contenu);
			error_malloc("fuz_lex", new_lexer->contenu);
			tmp_lexer = new_lexer->next->next;
			ft_free(new_lexer->next);
			new_lexer->next = tmp_lexer;
			if (tmp_lexer)
				tmp_lexer->pre = new_lexer;
		}
		else if (new_lexer->next)
			new_lexer = new_lexer->next;
	}
}

void	fuz_lex1(t_lexer **deb_lexer, int type)
{
	t_lexer	*new_lexer;
	t_lexer	*tmp_lexer;

	new_lexer = *deb_lexer;
	while (new_lexer && new_lexer->next && \
	ft_strncmp(new_lexer->contenu, "/n", 2))
	{
		if (new_lexer->type == CMD)
			new_lexer->type = MOT;
		if (new_lexer->type == type && (new_lexer->next->type == type \
			|| new_lexer->next->type == CMD))
		{
			new_lexer->contenu = ft_strjoin_2free(\
			new_lexer->contenu, new_lexer->next->contenu);
			error_malloc("fuz_lex", new_lexer->contenu);
			tmp_lexer = new_lexer->next->next;
			ft_free(new_lexer->next);
			new_lexer->next = tmp_lexer;
			if (tmp_lexer)
				tmp_lexer->pre = new_lexer;
		}
		else if (new_lexer->next)
			new_lexer = new_lexer->next;
	}
}

void	free_one_ele(t_lexer *tmp_lexer, t_lexer *to_free)
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
	ft_free(to_free->contenu);
	ft_free(to_free);
}

void	free_one_element(t_lexer **deb_lexer, t_lexer *tmp_lexer)
{
	t_lexer	*to_free;

	to_free = tmp_lexer;
	if (!tmp_lexer || !*deb_lexer)
		return ;
	if (!tmp_lexer->pre)
	{
		tmp_lexer = tmp_lexer->next;
		*deb_lexer = tmp_lexer;
		if (!to_free->pre && tmp_lexer)
			tmp_lexer->pre = NULL;
		ft_free(to_free->contenu);
		ft_free(to_free);
	}
	else
		free_one_ele(tmp_lexer, to_free);
	to_free = NULL;
}

int	len_lexer(t_lexer **deb_lexer)
{
	t_lexer	*tmp_lexer;
	int		i;

	i = 0;
	tmp_lexer = *deb_lexer;
	while (tmp_lexer)
	{
		i++;
		tmp_lexer = tmp_lexer->next;
	}
	return (i);
}
