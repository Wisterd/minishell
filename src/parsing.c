/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:17:10 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/29 03:28:23 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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