/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:17:10 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/26 21:18:15 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_lexer	**create_deb_lexer()
{
	t_lexer	**deb_lexer;

	deb_lexer = malloc(sizeof(*deb_lexer));
	*deb_lexer = NULL;
	if (!deb_lexer)
		error_malloc("lexing");
	return (deb_lexer);
}

int	near_mot(t_lexer **deb_lexer)
{
	t_lexer	*tmp_lexer;

	tmp_lexer = *deb_lexer;
	while (tmp_lexer && tmp_lexer->next)
	{
		if (tmp_lexer->type == MOT && tmp_lexer->next->type == MOT)
			return (1);
		tmp_lexer = tmp_lexer->next;
	}
	return(0);
}

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
			while (tmp_lexer && ft_strncmp(tmp_lexer->contenu, str, 2))
			{
				if (!ft_strncmp(tmp_lexer->contenu, "\"", 1))
					tmp_lexer->type = CMD;
				else if (!ft_strncmp(tmp_lexer->contenu, "'", 1))
					tmp_lexer->type = CMD;
				else if (!ft_strncmp(str, "\"", 2) \
				&& !ft_strncmp(tmp_lexer->contenu, "$", 2))
				 	tmp_lexer->type = DOLLAR;
				else if (tmp_lexer->type == SPC)
					tmp_lexer->type = SPC;
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

int	have_type(t_lexer **deb_lexer, int type)
{
	t_lexer	*tmp_lexer;

	tmp_lexer = *deb_lexer;
	while (tmp_lexer)
	{
		if (tmp_lexer->type == type)
			return (1);
		tmp_lexer = tmp_lexer->next;
	}
	return (0);
}

void	remove_type(t_lexer **deb_lexer, int type)
{
	t_lexer	*tmp_lexer;
	t_lexer	*next;

	tmp_lexer = *deb_lexer;
	while (tmp_lexer)
	{
		next = tmp_lexer->next;
		if (tmp_lexer->type == type)
			free_one_element(deb_lexer, tmp_lexer);
		tmp_lexer = next;
	}
}

void	*parse(char *prompt)
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
		create_lexer(deb_lexer, chartostr('\n'), SPC);
		//print_lexer(deb_lexer);
		prompt = readline("> ");
		lexing(deb_lexer, prompt);
	}
	fuz_lex(deb_lexer, MOT);
	history(deb_lexer);
	if (!valide_lexer(deb_lexer))
	{
		free_lexer(deb_lexer);
		return (NULL); // 2 ERROR
	}
	while (near_mot(deb_lexer))
		fuz_lex(deb_lexer, MOT);
	fuz_lex(deb_lexer, SPC);
	//	word_or_cmd(deb_lexer);
	while (have_type(deb_lexer, QUOTE))
		remove_type(deb_lexer, QUOTE);
	// while (have_type(deb_lexer, CMD))
	// 	remove_type(deb_lexer, CMD);

	print_lexer(deb_lexer);
	if (*deb_lexer)
		printf("\n");
	while (have_type(deb_lexer, SPC))
		remove_type(deb_lexer, SPC);
	
	
	// -------- POur marine ------------

	// t_tab_parse	*tab_parse;
	// tab_parse = to_exec(deb_lexer);	
	// print_to_exec(tab_parse);

	// data->tab_parse = tab_parse;
	// init_data(data);
	// ft_fork(&data);

	// ---------------------------------	
	free_lexer(deb_lexer);
	
	//test_lexer(tab_lexer);
	//return (tab_lexer);
	return (NULL);
}

void	mini_exit(char *prompt)
{
	ft_garbage_collector(INIT, NULL);
	while (ft_strncmp(prompt, "exit", 4) != 0)
	{
		prompt = readline("minishell> ");
		if (prompt)
			parse(prompt);
	}
	rl_clear_history();
	ft_garbage_collector(END, NULL);
	exit(EXIT_SUCCESS);
}

// int	main(int ac, char **av, char *envp[])
// {
// 	// t_args_exec	*args_exec;
	

// 	// set_inoutfiles(&data);
// 	// set_redirs(&data);
	
	
// }