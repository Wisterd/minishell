/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitaires_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 23:56:59 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/26 18:55:03 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*chartostr(char c)
{
	char	*str;

	str =ft_malloc(2 * sizeof(char));
	if (!str)
		error_malloc("chartostr");
	str[0] = c;
	str[1] = '\0';
	return (str);
}

int	special_c(char *str)
{
	int				i;
	t_pars_error	error;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == ';' || str[i] == '(' \
		|| str[i] == ')' || str[i] == '&')
		{
			error.c = str[i];
			error.i = SPECIAL;
			print_error(error);
			return (SPECIAL);
		}
	i++;
	}
	return (1);
}
