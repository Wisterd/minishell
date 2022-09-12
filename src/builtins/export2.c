/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:42:56 by mvue              #+#    #+#             */
/*   Updated: 2022/09/12 19:43:12 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	search_replace_var_name(t_env *l_env, char *var_name, char *var_content)
{
	t_env	*list;

	list = l_env;
	while (list)
	{
		if (!ft_strcmp(list->var_name, var_name))
		{
			list->var_content = var_content;
			return (1);
		}
		list = list->next;
	}
	return (0);
}
