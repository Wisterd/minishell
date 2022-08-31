/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 21:01:27 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/29 20:58:59 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_add_history(char *history)
{
	static char	*ancient = NULL;

	if (!ancient)
	{
		ancient = ft_strdup_perm(history);
		error_malloc("add_history ft_strdup1", ancient);
		add_history(history);
	}
	else if (strncmp(ancient, history, ft_strlen(ancient) + 1))
	{
		free(ancient);
		add_history(history);
		ancient = ft_strdup_perm(history);
		error_malloc("add_history ft_strdup2", ancient);
	}
}

void	history(t_lexer **deb_lexer)
{
	t_lexer		*new_lexer;
	char		*history;

	history = ft_strdup_perm("");
	error_malloc("history", history);
	new_lexer = *deb_lexer;
	while (new_lexer)
	{
		history = ft_strjoin_1free_perm(history, new_lexer->contenu);
		error_malloc("history ft_strjoin_1free", history);
		new_lexer = new_lexer->next;
	}
	ft_add_history(history);
	free(history);
}
