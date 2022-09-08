/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 00:07:34 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/08 23:28:40 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	if_file(t_exec_data *data)
{
	if (chdir(data->args_exec->tab_args[1]) == -1)
	{
		if (!access(data->args_exec->tab_args[1], R_OK))
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(data->args_exec->tab_args[1], 2);
			ft_putstr_fd(": Not a directory\n", 2);
		}
		else
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(data->args_exec->tab_args[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		g_exit_stat = 1;
		return (0);
	}
	return (1);
}

void	change_pwd(t_exec_data *data)
{
	t_env	*cp;

	cp = data->l_env;
	while (cp)
	{
		if (!strncmp(cp->var_name, "PWD", 4))
		{
			ft_free_perm(cp->var_content);
			cp->var_content = ft_strdup_perm(ft_getcwd());
		}
		if (!strncmp(cp->var_name, "?PWD", 4))
		{
			ft_free_perm(cp->var_content);
			cp->var_content = ft_strdup_perm(ft_getcwd());
		}
		cp = cp->next;
	}
}

void	new_dir(t_exec_data *data)
{
	if (if_file(data))
		change_pwd(data);
}

void	ft_cd(t_exec_data *data)
{
	int	y;

	y = 1;
	if (data->args_exec->tab_args[y] && data->args_exec->tab_args[y + 1])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return ;
	}
	else if (data->args_exec->tab_args[y] \
	&& !strncmp(data->args_exec->tab_args[y], "/", 1))
		new_dir(data);
	else if (data->args_exec->tab_args[y])
		new_dir(data);
}
