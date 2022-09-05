/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:08:46 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/06 01:28:08 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}


int	ft_atoi_exit(char *str)
{
	long int	nb;
	int	i;
	int signe;

	i = 0;
	signe = 1;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] && str[i] == '0')
		i++;
	while(str[i] && ft_isdigit(str[i]))
		nb = str[i++] - 48 + nb * 10;
	if ((str[i] && !ft_isdigit(str[i])) || (nb > INT_MAX || (signe * nb < INT_MIN)))
		return (0);
	g_exit_stat = nb * signe;
	return (1);
}

void	ft_exit(t_exec_data *data)
{
	int	y;

	y = 1;
	if (data->args_exec->tab_args[y])
	{
		if (!ft_atoi_exit(data->args_exec->tab_args[y]))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(data->args_exec->tab_args[y], 2);
			ft_putstr_fd(" : numeric argument required\n", 2);
			g_exit_stat = 2;
			exit(g_exit_stat);
		}
	}
	if (data->args_exec->tab_args[y] && data->args_exec->tab_args[y + 1])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		g_exit_stat = 1;
		return ;
	}
	else
		ft_putstr_fd("exit\n",1);
	while (g_exit_stat < 256)
		g_exit_stat = g_exit_stat + 256;
	g_exit_stat = g_exit_stat % 256;
	exit(g_exit_stat);
}
