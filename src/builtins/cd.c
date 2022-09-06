/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 00:07:34 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/06 01:37:22 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_cd(t_exec_data	*data)
{
	int	y;

	y = 1;
	if (data->args_exec->tab_args[y] && data->args_exec->tab_args[y + 1])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return ;
	}
}