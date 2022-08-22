/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:23:37 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/22 22:55:42 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_lexer(t_lexer **deb_lexer)
{
	t_lexer	*new_lexer;

	new_lexer = *deb_lexer;
	while (new_lexer)
	{
	//	printf("-----------------------\n");
	//	printf("lexer n = %d \n", new_lexer->id);
		// printf("contenu = %s \n", new_lexer->contenu);
		// printf("type = %d \n", new_lexer->type);
		
		// if (new_lexer->next)
		// 	printf("id next n = %d \n", new_lexer->next->id);
		// if (new_lexer->pre)
		// 	printf("id pre n = %d \n", new_lexer->pre->id);
		// 
		printf("%s", new_lexer->contenu);
		new_lexer = new_lexer->next;
	}
}

void	history(t_lexer **deb_lexer)
{
	t_lexer	*new_lexer;
	char	*history;

	history = " ";
	new_lexer = *deb_lexer;
	while (new_lexer)
	{
		history = ft_strjoin_1free(history, new_lexer->contenu);
		new_lexer = new_lexer->next;
	}
	add_history(history);
	free(history);
}

void	add_lexer(t_lexer **deb_lexer, t_lexer *lexer)
{
	t_lexer	*new_lexer;

	new_lexer = *deb_lexer;
	while (new_lexer->next)
		new_lexer = new_lexer->next;
	new_lexer->next = lexer;
	lexer->pre = new_lexer;
	lexer->id = new_lexer->id + 1;
}

void	free_lexer(t_lexer **deb_lexer)
{
	t_lexer	*new_lexer;
	t_lexer	*tmp;

	new_lexer = *deb_lexer;
	while (new_lexer)
	{
		tmp = new_lexer;
		new_lexer = new_lexer->next;
		free(tmp->contenu);
		free(tmp);
	}
	free(deb_lexer);
	deb_lexer = NULL;
}

void	create_lexer(t_lexer **deb_lexer, char *str, int type)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		error_malloc("create_lexer");
	lexer->type = type;
	lexer->contenu = str;
	lexer->next = NULL;
	if (!*deb_lexer)
	{
		lexer->id = 0;
		lexer->pre = NULL;
		*deb_lexer = lexer;
	}
	else
		add_lexer(deb_lexer, lexer);
}

void	lexing(t_lexer **deb_lexer, char *prompt)
{
	int		i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '>' || prompt[i] == '<')
			create_lexer(deb_lexer, chartostr(prompt[i]), REDIR);
		else if (prompt[i] == '|')
			create_lexer(deb_lexer, chartostr(prompt[i]), PIPE);
		else if (prompt[i] == ' ')
			create_lexer(deb_lexer, chartostr(prompt[i]), SPC);
		else if (prompt[i] == '\'' || prompt[i] == '\"')
			create_lexer(deb_lexer, chartostr(prompt[i]), QUOTE);
		else if (prompt[i] == '$')
			create_lexer(deb_lexer, chartostr(prompt[i]), DOLLAR);
		else
			create_lexer(deb_lexer, chartostr(prompt[i]), MOT);
		i++;
	}
}
