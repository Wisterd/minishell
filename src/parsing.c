/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:17:10 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/25 20:24:02 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	mini_exit(char *prompt)
{
	while (ft_strncmp(prompt, "exit", 4) != 0)
	{
		prompt = readline("minishell> ");
		if (prompt)
			add_history(prompt);
		printf("%s \n",prompt);
	}
	clear_history();
	exit(EXIT_SUCCESS);
}

int main(int ac, char **av)
{
	char	*prompt;
	
	parse(ac, av);
	
	prompt = "1";
	mini_exit(prompt);
	

}