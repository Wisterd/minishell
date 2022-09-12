/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:08:59 by mvue              #+#    #+#             */
/*   Updated: 2022/09/12 20:10:56 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*prompt;
	t_exec_data	data;

	(void) ac;
	(void) av;
	ft_garbage_collector_perm(INIT, NULL);
	data.l_env = init_env(envp);
	signals();
	prompt = NULL;
	mini_exit(prompt, &data);
}
