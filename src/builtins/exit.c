/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:08:46 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/28 22:06:01 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int g_exit_stat = 0;

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}


int	ft_atoi_exit(char *str)
{
	unsigned long long int	nb;
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
	if(str[i] && !ft_isdigit(str[i]))
		return (0);
	if (nb < LONG_MAX || ((signe * nb) > LONG_MIN))
		g_exit_stat = nb * signe;
	return (1);
}

void	ft_exit1(char	**tab_args)//, int ac)
{
	int	y;
	int retour_error;

	y = 1;
	if (tab_args[y])
		if (!ft_atoi_exit(tab_args[y]))
		{
			printf("exit\nminishell: exit: %s : argument numérique nécessaire", tab_args[y]);
			g_exit_stat = 2;
			exit(g_exit_stat);
		}
	if (tab_args[y + 1] )//|| ac > 2)
	{
		printf("exit\nminishell: exit: trop d'arguments");
		g_exit_stat = 1;
		return ;
	}
	while (g_exit_stat < 256)
		g_exit_stat = g_exit_stat + 256;
	g_exit_stat = g_exit_stat % 256;
	printf("exit\n%d", g_exit_stat);
	exit(g_exit_stat);
}

// int main (int ac , char **av)
// {
	
// 	ft_exit(av, ac);
// }