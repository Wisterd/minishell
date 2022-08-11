/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:45:27 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/11 23:16:19 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	valide_redir(t_lexer *tmp_lexer)
{
	t_pars_error	error;

	if (tmp_lexer->type == REDIR)
	{	
		while (tmp_lexer->next && tmp_lexer->next->type == SPC)
			tmp_lexer = tmp_lexer->next;
		if (!tmp_lexer->next)
		{
			error.str = "newline";
			error.i = REDIR;
			print_error(error);
			return (0);
		}
		if (tmp_lexer->next->type == REDIR)
		{
			error.str = tmp_lexer->next->contenu;
			error.i = REDIR;
			print_error(error);
			return (0);
		}
	}
	return (1);
}

int	valide_pipe(t_lexer *tmp_lexer)
{
	t_pars_error	error;

	if (tmp_lexer->type == PIPE)
	{	
		while (tmp_lexer->next && tmp_lexer->next->type == SPC)
			tmp_lexer = tmp_lexer->next;
		if (!tmp_lexer->next || !tmp_lexer->pre || \
		tmp_lexer->next->type == PIPE || tmp_lexer->next->type == REDIR ||
		tmp_lexer->pre->type == PIPE || tmp_lexer->pre->type == REDIR)
		{
			error.str = "|";
			error.i = REDIR;
			print_error(error);
			return (0);
		}
	}
	return (1);
}

int	valide_lexer(t_lexer **deb_lexer)
{
	t_lexer	*tmp_lexer;

	tmp_lexer = *deb_lexer;
	while (tmp_lexer)
	{
		//valide_cmd();
		if (!valide_pipe(tmp_lexer))
			return (0);
		// valide_quote();
		if (!valide_redir(tmp_lexer))
			return(0);
		// valide_dollar();
		tmp_lexer = tmp_lexer->next;
	}
	return (1);

}