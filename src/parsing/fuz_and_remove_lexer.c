/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuz_and_remove_lexer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:04:37 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/12 16:23:53 by vbarbier         ###   ########.fr       */
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
