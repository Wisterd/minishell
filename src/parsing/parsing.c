/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:17:10 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/08 19:14:24 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parse(t_lexer **deb_lexer, char *prompt, t_exec_data *data)
{
	lexing(deb_lexer, prompt);
	while (in_quote(deb_lexer))
	{
		create_lexer(deb_lexer, chartostr('\n'), SPC);
		prompt = readline("> ");
		if (!prompt)
		{
			ft_putstr_fd("syntax error: unexpected end of file\n", 2);
			return (0);
		}
		lexing(deb_lexer, prompt);
	}
	fuz_lex(deb_lexer, MOT);
	history(deb_lexer);
	if (special_c(prompt) == SPECIAL)
		return (0);
	if (!valide_lexer(deb_lexer, data))
		return (0);
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
	if (!parse(deb_lexer, prompt, data))
	{
		free_lexer(deb_lexer);
		g_exit_stat = 2;
		return (NULL); 
	}
	//print_lexer(deb_lexer);
	//if (*deb_lexer)
	//	printf("\n");
	while (near_mot(deb_lexer))
		fuz_lex(deb_lexer, MOT);
	fuz_lex1(deb_lexer, MOT);
	while (have_type(deb_lexer, SPC))
		remove_type(deb_lexer, SPC);
	fuz_lex(deb_lexer, REDIR);
	
	// print_lexer(deb_lexer);
	//// -------- POur marine ------------

	// prb solo $ ou char "";
	tab_parse = to_exec(deb_lexer);	
	//print_to_exec(tab_parse);
	//print_lexer(deb_lexer);
	if (*deb_lexer)
	{
		data->tab_parse = tab_parse;
		
		init_data(data);
		g_exit_stat = ft_fork(data);
		if (!data->kill_heredoc)
		{
			unlink_heredocs(data);
			if (data->n_cmds == 1 && is_builtin(data->args_exec->tab_args[0]))
				ft_garbage_collector(END, NULL);
		}
	}
	// ---------------------------------	
	//free_lexer(deb_lexer);
	return (NULL);
}

void	mini_exit(char *prompt, t_exec_data *data)
{
	while (1)
	{
		if (prompt)
			free(prompt);
		prompt = readline("minishell> ");
		if (!prompt)
		{
			printf("exit\n");
			ft_garbage_collector_perm(END, NULL);
			exit(g_exit_stat);
		}
		else
		{
			ft_garbage_collector(INIT, NULL);
			parsing(prompt, data);
			ft_garbage_collector(END, NULL);
		}
	}
	ft_garbage_collector_perm(END, NULL);
	rl_clear_history();
	exit(g_exit_stat);
}
