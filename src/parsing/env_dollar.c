/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:37:16 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/12 16:37:58 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_lexer	*replace_env(t_lexer **deb_lexer, t_lexer *tmp_lexer, char *env)
{
	ft_free(tmp_lexer->next->contenu);
	tmp_lexer->next->contenu = ft_strdup(env);
	error_malloc("replace dollar", tmp_lexer->next->contenu);
	free_one_element(deb_lexer, tmp_lexer);
	return (tmp_lexer = *deb_lexer);
}

char	*for_env(char *str)
{
	int		i;
	char	*cp;

	i = 0;
	if (str[i] == '?')
		return (ft_strdup("?"));
	if (!str || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (str);
	while (str[i] && (ft_isalpha(str[i]) \
		|| str[i] == '_' || ft_isdigit(str[i])))
		i++;
	cp = ft_substr(str, 0, i);
	return (cp);
}

char	*for_env2(char *str)
{
	int		i;
	char	*cp;

	i = 0;
	if (!str || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (NULL);
	while (str[i] && (ft_isalpha(str[i]) \
		|| str[i] == '_' || ft_isdigit(str[i])))
		i++;
	if (!str[i])
		return (NULL);
	cp = ft_strdup(&str[i]);
	return (cp);
}
