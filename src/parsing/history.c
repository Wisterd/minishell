/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 21:01:27 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/26 23:04:13 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_add_history(char *history)
{
	static char	*ancient = NULL;

	if (!ancient)
	{
		ancient = ft_strdup(history);
		add_history(history);
	}
	else if (strncmp(ancient, history, ft_strlen(ancient)))
	{
		free(ancient);
		add_history(history);
		ancient = ft_strdup(history);
		// A free a la fin du programme !
	}
}

void	history(t_lexer **deb_lexer)
{
	t_lexer		*new_lexer;
	char		*history;

	history = ft_strdup("");
	if (!history)
		error_malloc("history");
	new_lexer = *deb_lexer;
	while (new_lexer)
	{
		history = ft_strjoin_1free(history, new_lexer->contenu);
		new_lexer = new_lexer->next;
	}
	ft_add_history(history);
	free(history);
}