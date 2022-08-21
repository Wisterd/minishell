/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:45:27 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/21 02:46:47 by vbarbier         ###   ########.fr       */
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

char	*erase_one(char *str)
{
	int	i;
	char *cp;

	i = 1;
	if (!str)
		cp = ft_strdup("\0");
	else
		cp = malloc(sizeof(char) * ft_strlen(str));
	if (!cp)
		error_malloc("erase one");
	while (str[i])
	{
		cp[i - 1] = str[i];
		i++;
	}
	cp[i - 1] = '\0';
	free(str);
	return (cp);
}

int erase_dollar(t_lexer **deb_lexer, t_lexer *tmp_lexer, char *env)
{
	if (!env)
	{
		if (!ft_isalpha(*tmp_lexer->next->contenu) \
		&& ft_strncmp(tmp_lexer->next->contenu, "_", 1) \
		&& ft_strncmp(tmp_lexer->next->contenu, "?", 1))
		{
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
			tmp_lexer->next->contenu = erase_one(tmp_lexer->next->contenu);
		}
		else
			free_one_element(deb_lexer, tmp_lexer->next);
		return (1);
	}
	return (0);
}

t_lexer	*replace_dollar(t_lexer **deb_lexer, t_lexer *tmp_lexer)
{
	char	*env;

	if (tmp_lexer->type == DOLLAR && tmp_lexer->next)
	{
		if (tmp_lexer->next->type == MOT || tmp_lexer->next->type == CMD)
		{
			env = getenv(tmp_lexer->next->contenu);
			if (erase_dollar(deb_lexer, tmp_lexer, env))
			{
				free_one_element(deb_lexer, tmp_lexer);
				tmp_lexer = *deb_lexer;
				return (tmp_lexer);
			}
			free(tmp_lexer->next->contenu);
			tmp_lexer->next->contenu = ft_strdup(env);
			if (!tmp_lexer->next->contenu)
				error_malloc("replace dollar");
			free_one_element(deb_lexer, tmp_lexer);
			tmp_lexer = *deb_lexer;
		}
	}
	return (tmp_lexer);
}

int	valide_lexer(t_lexer **deb_lexer)
{
	t_lexer	*tmp_lexer;

	tmp_lexer = *deb_lexer;
	while (tmp_lexer)
	{
		tmp_lexer = replace_dollar(deb_lexer, tmp_lexer);
		if (tmp_lexer)
		{
			if (!valide_pipe(tmp_lexer))
			return (0);
			if (!valide_redir(tmp_lexer))
			return(0);
		// if (valide_cmd(tmp_lexer))
		// 	return (0);???
		tmp_lexer = tmp_lexer->next;
		}
	}
	return (1);
}
