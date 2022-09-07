/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:40:27 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/07 22:16:39 by vbarbier         ###   ########.fr       */
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
	int	y;

	y = 1;
	while (data->tab_parse->tab_args[y])
	{
		if (y == 1 && option_n(data->tab_parse->tab_args[y]))
			;
		else if (data->tab_parse->tab_args[y] && data->tab_parse->tab_args[y + 1])
		{
			protected_putstr(data->tab_parse->tab_args[y], "ft_echo", data);
			protected_putstr(" ", "ft_echo", data);
		}
		else if (data->tab_parse->tab_args[y] && !data->tab_parse->tab_args[y + 1])	
			protected_putstr(data->tab_parse->tab_args[y], "ft_echo", data);
		y++;
	}
	if (data->tab_parse->tab_args[1] && !option_n(data->tab_parse->tab_args[1]))
		protected_putstr("\n", "ft_echo", data);
}
