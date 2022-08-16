/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:17:10 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/16 18:49:28 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_lexer	**create_deb_lexer()
{
	t_lexer	**deb_lexer;

	deb_lexer = malloc(sizeof(*deb_lexer));
	*deb_lexer = NULL;
	if (!deb_lexer)
		error_malloc("lexing");
	return (deb_lexer);
}
/*
int	pair_quote(t_lexer **deb_lexer)
{
	t_lexer	*tmp_lexer;
	int		dq;
	int		sq;
	static int	in_sq = 0;
	static int	in_dq = 0;

	tmp_lexer = *deb_lexer;
	dq = 0;
	sq = 0;
	while (tmp_lexer)
	{
		if ((in_sq && ft_strncmp(tmp_lexer->contenu, "'", 2) != 0)\
		|| (in_dq && ft_strncmp(tmp_lexer->contenu, "\"", 2) != 0))
			tmp_lexer->type = MOT;
		else if (tmp_lexer->type == QUOTE)
		{
			if (ft_strncmp(tmp_lexer->contenu, "'", 2) == 0)
			{
				if (!in_sq)
					in_sq = 1;
				else
					in_sq = 0;
				sq++;
			}	
			else if (ft_strncmp(tmp_lexer->contenu, "\"", 2) == 0)
			{
				if (!in_dq)
					in_dq = 1;
				else
					in_dq = 0;
				dq++;
			}
		}
		tmp_lexer = tmp_lexer->next;
	}
	printf("sq = %d  dq= %d\n", sq, dq);
	if (dq % 2 != 0 || sq % 2 != 0)
		return (0);
	return (1);
}
*/
int	in_quote(t_lexer **deb_lexer)
{
	char	*str;
	t_lexer	*tmp_lexer;

	tmp_lexer = *deb_lexer;
	while (tmp_lexer)
	{
		if (tmp_lexer->type == QUOTE)
		{
			if (!tmp_lexer->next)
				return(1);
			str = tmp_lexer->contenu;
			tmp_lexer = tmp_lexer->next;
			while (tmp_lexer && ft_strncmp(tmp_lexer->contenu, str, 2) != 0)
			{
				if (ft_strncmp(str, "'", 2) == 0 \
				&& ft_strncmp(tmp_lexer->contenu, "$", 2) == 0)
					tmp_lexer->type = DOLLAR;
				else
					tmp_lexer->type = MOT;
				tmp_lexer = tmp_lexer->next;
				if (!tmp_lexer)
					return(1);
			}
		}
		tmp_lexer = tmp_lexer->next;
	}
	return (0);
}

void *parse(char *prompt)
{
	t_lexer	**deb_lexer;

	deb_lexer = create_deb_lexer();
	if (special_c(prompt) == SPECIAL)
	{
		free_lexer(deb_lexer);
		return (NULL); //error
	}
	lexing(deb_lexer, prompt);
	while (in_quote(deb_lexer))
	{
		//create_lexer(deb_lexer, chartostr(' '), SPC);
		//print_lexer(deb_lexer);
		prompt = readline("> ");
		lexing(deb_lexer, prompt);
	}
	fuz_lex(deb_lexer, MOT);
	fuz_lex(deb_lexer, SPC);
	word_or_cmd(deb_lexer);
	if (!valide_lexer(deb_lexer))
	{
	//	print_lexer(deb_lexer);
		free_lexer(deb_lexer);
		return (NULL);
	}
	print_lexer(deb_lexer);
	free_lexer(deb_lexer);
	
	//test_lexer(tab_lexer);
	//return (tab_lexer);
	return (NULL);
}

void	mini_exit(char *prompt)
{
	while (ft_strncmp(prompt, "exit", 4) != 0)
	{
		prompt = readline("minishell> ");
		if (prompt)
		{
			parse(prompt);
			add_history(prompt);
		}
		//printf("%s \n",prompt);
	}
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

int main()
{
	char	*prompt;
	prompt = NULL;
	mini_exit(prompt);
}