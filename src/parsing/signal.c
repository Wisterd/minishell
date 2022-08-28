/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 06:05:43 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/27 18:59:10 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../inc/minishell.h"

void	catch_signals(int signum)
{
	if (signum == SIGINT)
	{
	
		g_exit_stat = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
		g_exit_stat = 131;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signals()
{
	struct sigaction	sa;
	int					fail;

	fail = 0;
	sa.sa_handler = &catch_signals;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	fail = sigaction(SIGINT, &sa, NULL);
	if (fail == -1)
		exit(EXIT_FAILURE);
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	fail = sigaction(SIGQUIT, &sa, NULL);
	if (fail == -1)
		exit(EXIT_FAILURE);
	// printf("fail = %d\n", fail);

	//sigaction(SIGMINE, &sa, NULL); CTRL-D ???
}
// int sigaction(int signum, const struct sigaction *act,
// struct sigaction *oldact);