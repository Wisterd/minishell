/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 00:01:00 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/08 00:01:33 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void fuz_lex_word(t_lexer **deb_lexer)
{
	t_lexer	*new_lexer;
	t_lexer	*tmp_lexer;

	new_lexer = *deb_lexer;
	while (new_lexer && new_lexer->next)
	{
		if (new_lexer->type == MOT && new_lexer->next->type == MOT)
		{
			new_lexer->contenu = ft_strjoin_free(new_lexer->contenu, new_lexer->next->contenu);
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
