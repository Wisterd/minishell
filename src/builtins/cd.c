/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 00:07:34 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/06 00:31:10 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_cd(t_exec_data	*data)
{
	int	y;

	y = 1;
	if (data->tab_parse->tab_args[2])
		protected_putstr(data->tab_parse->tab_args[y], "ft_echo", data);
}