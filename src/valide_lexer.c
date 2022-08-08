/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:45:27 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/08 17:45:00 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	valide_redir(t_lexer *tmp_lexer)
{
	t_pars_error	error;

	if (tmp_lexer->type == REDIR)
	{
		if (!tmp_lexer->pre)
		{
			error.str = tmp_lexer->contenu;
			error.i = SPECIAL;
			print_error(error);
			return (0);
		}
	}
	return (1);
}

void	valide_lexer(t_lexer **deb_lexer)
{
	t_lexer	*tmp_lexer;

	tmp_lexer = *deb_lexer;
	while (tmp_lexer)
	{
		//valide_cmd();
		// valide_pipe();
		// valide_quote();
		if (!valide_redir(tmp_lexer))
		{
			free_lexer(deb_lexer);
		//	return(NULL);
		}
		// valide_dollar();
		tmp_lexer = tmp_lexer->next;
	}

}