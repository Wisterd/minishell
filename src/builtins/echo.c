/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:40:27 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/08 19:51:59 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	option_n(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-')
		return (0);
	i++;
	while (str[i] == 'n')
		i++;
	if (!str[i])
		return (1);
	else
		return (0);
}

void	ft_echo(t_exec_data	*data)
{
	int		y;
	char	**args;

	args = data->tab_parse[data->ind_cmd].tab_args;
	y = 1;
	while (args[y])
	{
		if (y == 1 && option_n(args[y]))
			;
		else if (args[y] && args[y + 1])
		{
			if (protected_putstr(args[y], "ft_echo", data) == -1)
				return ;
			protected_putstr(" ", "ft_echo", data);
		}
		else if (args[y] && !args[y + 1])
			protected_putstr(args[y], "ft_echo", data);
		y++;
	}
	if (!args[1] || (args[1] && !option_n(args[1])))
		protected_putstr("\n", "ft_echo", data);
	g_exit_stat = 0;
}
