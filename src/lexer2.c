/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 00:01:00 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/08 17:57:21 by vbarbier         ###   ########.fr       */
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
			new_lexer->contenu = ft_strjoin_free(\
			new_lexer->contenu, new_lexer->next->contenu);
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

int	is_cmd(char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(str, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(str, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(str, "export" , 7) == 0)
		return (1);
	if (ft_strncmp(str, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(str, "env", 4) == 0)
		return (1);
	return (0);
	
}

void	word_or_cmd(t_lexer **deb_lexer)
{
	t_lexer	*new_lexer;

	new_lexer = *deb_lexer;
	while (new_lexer)
	{
		if (new_lexer->type == MOT)
			if (is_cmd(new_lexer->contenu))
				new_lexer->type = CMD;			
		new_lexer = new_lexer->next;
	}
}