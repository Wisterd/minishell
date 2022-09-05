/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 00:28:48 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/06 00:42:59 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_exec_data *data)
{
	if (ft_getcwd())
	{
		protected_putstr(ft_getcwd(), "ft_pwd", data);
		protected_putstr("\n", "ft_pwd", data);
		return (0);
	}
	return (1);
}
