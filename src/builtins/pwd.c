/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 00:28:48 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/07 20:12:41 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_exec_data *data)
{
	t_env	*cp;
	char	*str;
	
	cp = data->l_env;
	while (cp)
	{
		if (!strncmp(cp->var_name, "?PWD", 4))
			str = cp->var_content;
		cp = cp->next;
	}
	if (str)
	{
		protected_putstr(str, "ft_pwd", data);
		protected_putstr("\n", "ft_pwd", data);
		return (0);
	}
	return (1);
}
