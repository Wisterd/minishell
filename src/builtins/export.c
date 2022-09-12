/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:50:31 by mvue              #+#    #+#             */
/*   Updated: 2022/09/12 21:29:27 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_export_error(char *arg, t_exec_data *data)
{
	char	*to_write;

	write(2, "export: '", 8);
	to_write = ft_strjoin_1free(arg, "': not a valid identifier\n");
	if (!to_write)
		ft_error(ERR_MALLOC, NULL, data);
	write(2, to_write, ft_strlen(to_write));
}

static int	check_valid_export(char *var_name)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(var_name[i]) || var_name[i] == '_'))
		return (0);
	i++;
	while (var_name[i] != '=' && var_name[i])
	{
		if (!(ft_isalnum(var_name[i]) || var_name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int	has_equal_sign(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static void	loop_on_export(t_exec_data *data, char *arg)
{
	char	*var_name;
	char	*var_content;

	if (!check_valid_export(arg))
	{
		print_export_error(arg, data);
		g_exit_stat = 1;
	}
	else if (!has_equal_sign(arg))
		return ;
	else
	{
		var_name = get_var_name(arg);
		var_content = get_var_content(arg);
		if (search_replace_var_name(data->l_env, var_name, var_content))
			return ;
		l_add_back(&data->l_env, var_name, var_content);
	}
}

void	ft_export(t_exec_data *data)
{
	char	**tab_args;
	int		i;

	tab_args = data->tab_parse[data->ind_cmd].tab_args;
	g_exit_stat = 0;
	if (!tab_args[1])
	{
		ft_env(data);
		return ;
	}
	i = 1;
	while (tab_args[i])
	{
		loop_on_export(data, tab_args[i]);
		i++;
	}
	g_exit_stat = 0;
}
