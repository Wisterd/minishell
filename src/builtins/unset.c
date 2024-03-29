/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:43:29 by mvue              #+#    #+#             */
/*   Updated: 2022/09/12 21:30:38 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_list_var(t_env *list)
{
	ft_free_perm(list->var_name);
	list->var_name = NULL;
	ft_free_perm(list);
}

static void	rm_var(t_exec_data *data, char *var_name)
{
	t_env	*list;

	list = data->l_env;
	while (list)
	{
		if (!ft_strncmp(list->var_name, var_name, ft_strlen(var_name)))
		{
			if (!list->prev && list->next)
			{
				list->next->prev = NULL;
				data->l_env = list->next;
			}
			if (!list->next && list->prev)
				list->prev->next = NULL;
			if (list->next && list->prev)
			{
				list->prev->next = list->next;
				list->next->prev = list->prev;
			}
			free_list_var(list);
			return ;
		}
		list = list->next;
	}
}

int	check_valid_unset(char *var_name)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(var_name[i]) || var_name[i] == '_'))
		return (0);
	i++;
	while (var_name[i])
	{
		if (!(ft_isalnum(var_name[i]) || var_name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static void	print_unset_error(char *arg, t_exec_data *data)
{
	char	*to_write;

	write(2, "unset: '", 8);
	to_write = ft_strjoin_1free(arg, "': not a valid identifier\n");
	if (!to_write)
		ft_error(ERR_MALLOC, NULL, data);
	write(2, to_write, ft_strlen(to_write));
}

void	ft_unset(t_exec_data *data)
{
	char	**tab_args;
	int		i;

	tab_args = data->tab_parse[data->ind_cmd].tab_args;
	g_exit_stat = 0;
	if (!tab_args[1])
		return ;
	i = 0;
	while (tab_args[i])
	{
		if (!check_valid_unset(tab_args[i]))
		{
			print_unset_error(tab_args[i], data);
			g_exit_stat = 1;
		}
		else
			rm_var(data, tab_args[i]);
		i++;
	}
}
