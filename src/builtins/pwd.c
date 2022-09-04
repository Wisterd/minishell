/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:42:06 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/04 22:26:55 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_exec_data *data)
{
	char	*path;
	
	path = ft_getenv("PATH", data);
	if (!path)
		return (1);
	if (getcwd(path, ft_strlen(path)))
	{
		protected_putstr(path, "ft_pwd", data);
		return (0);
	}
	return (1);
}