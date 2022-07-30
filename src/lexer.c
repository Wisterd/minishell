/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:23:37 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/30 04:24:04 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *chartostr(char c)
{
	char *str;

	str = malloc(2 * sizeof(char));
	str[0] = c;
	str[1] = '\0';
	return (str);
 }

void print_error(t_pars_error error)
{
	if (error.i == SPECIAL)
		printf("erreur de syntaxe près du symbole inattendu « %c »\n", error.c);
	if (error.i == ERROR_MALLOC)
		printf("erreur d'allocation de memoire, fonction %s", error.fct);
}

void	error_malloc(char *str)
{
	t_pars_error	error;
	error.i = ERROR_MALLOC;
	error.fct = str;
	print_error(error);
}

int	special_c(char *str)
{
	int 			i;
	t_pars_error	error;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == ';' || str[i] == '(' || str[i] == ')' || str[i] == '&')
		{
			error.c = str[i];
			error.i = SPECIAL;
			print_error(error);
			return (SPECIAL);
		}
	i++;
	//	if (str[i] == '\\' || str[i] == '>' ||  str[i] == '|' ||  str[i] == '<' 
	//	|| str[i] == ';' || str[i])

	//	if (str[i] == '$')
	}
	return (1);
}

void	print_lexer(t_lexer **deb_lexer)
{
	t_lexer *new_lexer;

	new_lexer = *deb_lexer;
	while (new_lexer)
	{
		printf("-----------------------\n");
		printf("lexer n = %d \n", new_lexer->id);
		printf("contenu = %s \n", new_lexer->contenu);
		printf("type = %d \n", new_lexer->type);
		/*
		if (new_lexer->next)
			printf("id next n = %d \n", new_lexer->next->id);
		if (new_lexer->pre)
			printf("id pre n = %d \n", new_lexer->pre->id);
		*/
		new_lexer = new_lexer->next;
	}
}

void	add_lexer(t_lexer **deb_lexer, t_lexer *lexer)
{
	t_lexer *new_lexer;

	new_lexer = *deb_lexer;
	while (new_lexer->next)
		new_lexer = new_lexer->next;
	new_lexer->next = lexer;
	lexer->pre = new_lexer;
	lexer->id = new_lexer->id + 1;
}

void	create_lexer(t_lexer **deb_lexer, char *str, int type)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if(!lexer)
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

t_lexer	**lexing(char *prompt)
{
	int		i;
	t_lexer	**deb_lexer;

	deb_lexer = malloc(sizeof(*deb_lexer));
	*deb_lexer = NULL;
	if (!deb_lexer)
		error_malloc("lexing");
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
			create_lexer(deb_lexer, chartostr(prompt[i]) , MOT);
		i++;
	}
	return (deb_lexer);
}
	
t_lexer **fuz_lex_word(t_lexer	**deb_lexer)
{
	//join contenu
	t_lexer	*new_lexer;

	new_lexer = *deb_lexer;
	while (new_lexer->next)
	{
		if (new_lexer->type == MOT && new_lexer->type == new_lexer->next->type)
		{
			new_lexer->contenu = ft_strjoin(new_lexer->contenu, new_lexer->next->contenu);
			new_lexer->id
		}
		new_lexer = new_lexer->next;
	}
}
void *parse(char *prompt)
{
	t_lexer	**deb_lexer;
	
	if (special_c(prompt) == SPECIAL)
		return (NULL);
	deb_lexer = lexing(prompt);
	fuz_lex_word(deb_lexer);
	print_lexer(deb_lexer);
	//tab_lexer = malloc((ac - 1) * sizeof(t_lexer));
	//tab_lexer[i - 1] = create_lexer(prompt, ac);
	//test_lexer(tab_lexer);
	//return (tab_lexer);
	return (NULL);
}
