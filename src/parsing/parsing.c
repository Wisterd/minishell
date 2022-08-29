/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:17:10 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/29 22:18:33 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parse(t_lexer **deb_lexer, char *prompt)
{
	lexing(deb_lexer, prompt);
	while (in_quote(deb_lexer))
	{
		create_lexer(deb_lexer, chartostr('\n'), SPC);
		prompt = readline("> ");
		lexing(deb_lexer, prompt);
	}
	fuz_lex(deb_lexer, MOT);
	history(deb_lexer);
	if (special_c(prompt) == SPECIAL)
	{
		free_lexer(deb_lexer);
		return (0);
	}
	if (!valide_lexer(deb_lexer))
	{
		free_lexer(deb_lexer);
		return (0);
	}
	while (near_mot(deb_lexer))
		fuz_lex(deb_lexer, MOT);
	fuz_lex(deb_lexer, SPC);
	while (have_type(deb_lexer, QUOTE))
		remove_type(deb_lexer, QUOTE);
	return (1);
}

void	*parsing(char *prompt, t_exec_data *data)
{
	t_lexer		**deb_lexer;
	t_tab_parse	*tab_parse;

	deb_lexer = create_deb_lexer();
	if (!parse(deb_lexer, prompt))
	{
		g_exit_stat = 2;
		return (NULL); 
	}
	//print_lexer(deb_lexer);
	//if (*deb_lexer)
	//	printf("\n");
	while (near_mot(deb_lexer))
		fuz_lex(deb_lexer, MOT);
	while (have_type(deb_lexer, SPC))
		remove_type(deb_lexer, SPC);
	fuz_lex(deb_lexer, REDIR);
	
	// print_lexer(deb_lexer);
	//// -------- POur marine ------------

	// prb solo $ ou char "";
	tab_parse = to_exec(deb_lexer);	
	// print_to_exec(tab_parse);
	if (*deb_lexer)
	{
		data->tab_parse = tab_parse;
		init_data(data);
		ft_fork(data);
	}
	// ---------------------------------	
	free_lexer(deb_lexer);
	return (NULL);
}

void	mini_exit(char *prompt, t_exec_data *data)
{
	while (ft_strncmp(prompt, "exit", 4) != 0)
	{
		prompt = readline("minishell> ");
		if (!prompt)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		else
			parsing(prompt, data);
	}
	rl_clear_history();
	ft_garbage_collector(END, NULL);
	exit(EXIT_SUCCESS);
}
