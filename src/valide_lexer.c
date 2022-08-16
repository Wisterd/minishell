/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:45:27 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/16 19:15:18 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	mult_redir(t_lexer *tmp_lexer)
{
	t_pars_error	error;

	if (tmp_lexer->next->type == REDIR)
	{
		error.str = tmp_lexer->next->contenu;
		error.i = REDIR;
		if (!tmp_lexer->next->next)
			;
		else if (tmp_lexer->next->next->type == REDIR \
		&& !(ft_strncmp(tmp_lexer->next->next->contenu, \
		tmp_lexer->next->contenu, 2)))
		{
			error.str = tmp_lexer->next->contenu;
			error.i = REDIR2;
		}
		print_error(error);
		return (0);
	}
	return (1);
}

int	valide_redir(t_lexer *tmp_lexer)
{
	t_pars_error	error;

	if (tmp_lexer->type == REDIR)
	{	
		if (tmp_lexer->next && tmp_lexer->next->type == REDIR \
		&& !(ft_strncmp(tmp_lexer->next->contenu, tmp_lexer->contenu, 2)))
			tmp_lexer = tmp_lexer->next;
		while (tmp_lexer->next && tmp_lexer->next->type == SPC)
			tmp_lexer = tmp_lexer->next;
		if (!tmp_lexer->next)
		{
			error.str = "newline";
			error.i = REDIR;
			print_error(error);
			return (0);
		}
		if (!mult_redir(tmp_lexer))
			return (0);
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
		tmp_lexer->next->type == PIPE || tmp_lexer->next->type == REDIR \
		|| tmp_lexer->pre->type == PIPE || tmp_lexer->pre->type == REDIR)
		{
			error.str = "|";
			error.i = REDIR;
			print_error(error);
			return (0);
		}
	}
	return (1);
}

void	replace_dollar(t_lexer **deb_lexer, t_lexer *tmp_lexer)
{
	char	*env;

	if (tmp_lexer->type == DOLLAR && tmp_lexer->next)
	{
		if (tmp_lexer->next->type == MOT || tmp_lexer->next->type == CMD)
		{
			env = getenv(tmp_lexer->next->contenu);
			if (!env)
				return ;
			free(tmp_lexer->next->contenu);
			tmp_lexer->next->contenu = ft_strdup(env);
			if (tmp_lexer->pre)
			{
				tmp_lexer->pre->next = tmp_lexer->next;
				tmp_lexer->next->pre = tmp_lexer->pre;
			}
			else
			{
				tmp_lexer->next->pre = NULL;
				*deb_lexer = tmp_lexer->next;
			}
			free(tmp_lexer->contenu);
			free(tmp_lexer);
		}
	}
	//return (1);
}

int	valide_lexer(t_lexer **deb_lexer)
{
	t_lexer	*tmp_lexer;

	tmp_lexer = *deb_lexer;
	while (tmp_lexer)
	{
		if ((tmp_lexer->pre && !strncmp(tmp_lexer->pre->contenu, "\'", 1) == 0) \
		|| !tmp_lexer->pre)
			replace_dollar(deb_lexer, tmp_lexer);
		if (!valide_pipe(tmp_lexer))
			return (0);
		if (!valide_redir(tmp_lexer))
			return(0);
		// if (valide_cmd(tmp_lexer))
		// 	return (0);???
		
		tmp_lexer = tmp_lexer->next;
	}
	return (1);
}
