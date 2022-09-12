/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:28:13 by mvue              #+#    #+#             */
/*   Updated: 2022/09/12 22:50:31 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_getenv(char *to_get, t_exec_data *data)
{
	t_env	*list;

	list = data->l_env;
	while (list)
	{
		if (!ft_strcmp(list->var_name, to_get))
			return (list->var_content);
		list = list->next;
	}
	return (NULL);
}

int	get_last_list_env(t_env *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

char	**ft_get_total_env(t_exec_data *data)
{
	char	**tab_env;
	t_env	*list;
	int		i;

	list = data->l_env;
	i = get_last_list_env(list);
	tab_env = ft_malloc(sizeof(char *) * (i + 1));
	if (!tab_env)
		ft_error(ERR_MALLOC, NULL, data);
	list = data->l_env;
	i = 0;
	while (list->next)
	{
		tab_env[i] = ft_strjoin(list->var_name, "=");
		if (!tab_env[i])
			ft_error(ERR_MALLOC, NULL, data);
		tab_env[i] = ft_strjoin(tab_env[i], list->var_content);
		if (!tab_env[i])
			ft_error(ERR_MALLOC, NULL, data);
		i++;
		list = list->next;
	}
	tab_env[i] = NULL;
	return (tab_env);
}

int	protected_write_env(t_exec_data *data)
{
	if (protected_putstr(data->l_env->var_name, "env", data) == -1)
		return (-1);
	if (protected_putstr("=", "env", data) == -1)
		return (-1);
	if (protected_putstr(data->l_env->var_content, "env", data) == -1)
		return (-1);
	if (protected_putstr("\n", "env", data) == -1)
		return (-1);
	return (0);
}

void	ft_env(t_exec_data *data)
{
	t_env	*start_list;

	if (data->args_exec->tab_args[1])
	{
		g_exit_stat = 1;
		write(2, "env: too many arguments\n", 24);
	}
	else
	{
		start_list = data->l_env;
		while (data->l_env)
		{
			if (data->l_env->var_name && ft_strncmp("?", \
				data->l_env->var_name, 1))
				if (protected_write_env(data) == -1)
					return ;
			data->l_env = data->l_env->next;
		}
		data->l_env = start_list;
	}
	g_exit_stat = 0;
}
