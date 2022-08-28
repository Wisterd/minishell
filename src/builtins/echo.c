/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:40:27 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/28 17:02:57 by vbarbier         ###   ########.fr       */
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

void	ft_echo(char	**tab_args, int ac)
{
	int	y;
	int opt_n;

	y = 1;
	opt_n = 0;
	while (tab_args[y] || y < ac)
	{
		if (y == 1 && option_n(tab_args[y]))
		{
			opt_n = 1;
			y++;
		}
		if (tab_args[y + 1])
			printf("%s ", tab_args[y]);
		if (!tab_args[y + 1])	
			printf("%s", tab_args[y]);
		y++;
	}
	if (!opt_n && tab_args[1])
		printf("\n");
}

int main (int ac , char **av)
{
	ft_echo(av, ac);
}