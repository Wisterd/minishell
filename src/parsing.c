/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:17:10 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/20 20:18:41 by vbarbier         ###   ########.fr       */
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
		if (ft_strncmp(prompt, "clear", 7) == 0)
		{
			clear_history();
		}
		printf("%s \n",prompt);
	}
	exit(EXIT_SUCCESS);
}

int main(void)//(int ac, char **av)
{
	char	*prompt;

	prompt = "1";
	mini_exit(prompt);
	

}