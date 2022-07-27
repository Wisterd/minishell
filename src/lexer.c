/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:23:37 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/27 17:08:23 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void print_error(int i)
{

}

int	is_word(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == ';' || str[i] == '(' || str[i] == ')' || str[i] == '&')
		
		if (str[i] == '\\' || str[i] == '>' ||  str[i] == '|' ||  str[i] == '<' \
		|| str[i] == ';' || str[i])

		if (str[i] == '$')
	}

}

/*
int	type_lexer(char *str)
{
	if 
	if (is_pipe(str))
		return (PIPE);
}
*/


t_lexer	create_lexer(char *prompt)
{
	static int id = 0;
	t_lexer	lexer;

	lexer.id = id;
	id++;
	lexer.type = type_lexer(prompt);
	lexer.contenu = ft_strdup(prompt);
	if (lexer.id == 0)
		lexer.pre = NULL;
	lexer.next = NULL;
	if (lexer.pre)
		lexer.next = &lexer;
	return (lexer);
}

t_lexer *parse(char *prompt)

	t_lexer *tab_lexer;

	while (!prompt)
	{
		if (is_word())
		prompt++;
	}
	//tab_lexer = malloc((ac - 1) * sizeof(t_lexer));
	tab_lexer[i - 1] = create_lexer(prompt, ac);
	test_lexer(tab_lexer);
	return (tab_lexer);
}
