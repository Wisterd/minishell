/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:17:10 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/08 17:33:59 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void *parse(char *prompt)
{
	t_lexer	**deb_lexer;
	
	if (special_c(prompt) == SPECIAL)
		return (NULL);
	deb_lexer = lexing(prompt);
	fuz_lex(deb_lexer, MOT);
	fuz_lex(deb_lexer, SPC);
	word_or_cmd(deb_lexer);
	
	print_lexer(deb_lexer);
	free_lexer(deb_lexer);
	
	//valide ?
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
		printf("%s \n",prompt);
	}
	rl_clear_history();
	// free les str du lexer , la lst de lexer et le lexer;
	exit(EXIT_SUCCESS);
}

int main()
{
	char	*prompt;
	prompt = NULL;
	mini_exit(prompt);
}