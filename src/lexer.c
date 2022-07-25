/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:23:37 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/25 20:42:41 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*
int	id_lexer(char *str)
{
	if 
	if (is_pipe(str))
		return (PIPE);
}
*/
t_lexer	create_lexer(char *str, int ac)
{
	static int id = 0;
	t_lexer	lexer;

	lexer.id = id;
	id++;
	lexer.contenu = ft_strdup(str);
	if (lexer.id == 0)
		lexer.pre = NULL;
	if (lexer.id == ac - 1)
		lexer.next = NULL;
	return (lexer);
}

t_lexer *parse(int ac, char **av)
{
	int		i;
	t_lexer *tab_lexer;

	if (ac <= 1)
		return (NULL);
	i = 1;
	tab_lexer = malloc((ac - 1) * sizeof(t_lexer));
	while (i < ac)
	{
		tab_lexer[i - 1] = create_lexer(av[i], ac);
		i++;
	}
	test_lexer(tab_lexer);
	return (tab_lexer);
}
