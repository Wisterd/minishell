/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_lexer_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:40:42 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/29 20:53:18 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*erase_one(char *str)
{
	int	i;
	char *cp;

	i = 1;
	if (!str)
		cp = ft_strdup("\0");
	else
		cp = ft_malloc(sizeof(char) * ft_strlen(str));
	error_malloc("erase_one", cp);
	while (str[i])
	{
		cp[i - 1] = str[i];
		i++;
	}
	cp[i - 1] = '\0';
	ft_free(str);
	return (cp);
}

int	is_question(t_lexer *tmp_lexer)
{
	if (!ft_strncmp(tmp_lexer->next->contenu, "?", 1))
	{
		ft_free(tmp_lexer->next->contenu);
		tmp_lexer->next->contenu = ft_itoa(g_exit_stat);
		error_malloc("is_question", tmp_lexer->next->contenu);
		return (1);
	}
	return (0);
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
		else if (is_question(tmp_lexer))
			return (1);
		else
			free_one_element(deb_lexer, tmp_lexer->next);
		return (1);
	}
	return (0);
}

t_lexer	*replace_dollar(t_lexer **deb_lexer, t_lexer *tmp_lexer)
{
	char	*env;

	if (tmp_lexer && tmp_lexer->next && tmp_lexer->type == DOLLAR)
	{
		while (tmp_lexer->next->type == DOLLAR)
		{
			free_one_element(deb_lexer, tmp_lexer);
			tmp_lexer = *deb_lexer;
			return (tmp_lexer);
		}
		if (tmp_lexer->next->type == MOT)
		{
			env = getenv(tmp_lexer->next->contenu); // Recup  env marine
			if (erase_dollar(deb_lexer, tmp_lexer, env))
			{
				free_one_element(deb_lexer, tmp_lexer);
				tmp_lexer = *deb_lexer;
				return (tmp_lexer);
			}
			ft_free(tmp_lexer->next->contenu);
			tmp_lexer->next->contenu = ft_strdup(env);
			error_malloc("replace dollar", tmp_lexer->next->contenu);
			free_one_element(deb_lexer, tmp_lexer);
			tmp_lexer = *deb_lexer;
		}
	}
	return (tmp_lexer);
}
