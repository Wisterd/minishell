/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:40:27 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/03 19:05:39 by vbarbier         ###   ########.fr       */
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

void	ft_echo(t_exec_data	*data)//**tab_args)//, int ac)
{
	int	y;
	int opt_n;

	y = 1;
	opt_n = 0;
	while (data->tab_parse->tab_args[y])// || y < ac)
	{
		if (y == 1 && option_n(data->tab_parse->tab_args[y]))
		{
			opt_n = 1;
			y++;
		}
		if (data->tab_parse->tab_args[y + 1])
		{
			protected_putstr(data->tab_parse->tab_args[y], "ft_echo", data);
			protected_putstr(" ", "ft_echo", data);
		}
		if (!data->tab_parse->tab_args[y + 1])	
			protected_putstr(data->tab_parse->tab_args[y], "ft_echo", data);
		y++;
	}
	if (!opt_n && data->tab_parse->tab_args[1])
		protected_putstr("\n", "ft_echo", data);
}

// int main (int ac , char **av)
// {
// 	ft_echo(av, ac);
// }