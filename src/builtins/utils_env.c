/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:42:45 by mvue              #+#    #+#             */
/*   Updated: 2022/09/12 23:05:24 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	protected_putstr(char *str, char *builtin, t_exec_data *data)
{
	char	*msg;

	if (write(data->fd_out_builtin, str, ft_strlen(str)) == -1)
	{
		msg = ft_strjoin(builtin, ": write error: no space left on device\n");
		if (!msg)
			ft_error(ERR_MALLOC, NULL, data);
		write(2, msg, ft_strlen(msg));
		g_exit_stat = 1;
		return (-1);
	}
	return (0);
}

char	*get_var_content(char *var_path)
{
	char	*var_content;

	if (!var_path)
		return (NULL);
	while (*var_path != '=')
		var_path++;
	var_path++;
	if (!*var_path)
		var_content = ft_strdup_perm("");
	else
		var_content = ft_strdup_perm(var_path);
	if (!var_content)
		ft_error(ERR_MALLOC, NULL, NULL);
	return (var_content);
}

char	*get_var_name(char *var_path)
{
	char	*var_name;
	char	*str_cpy;
	int		i;

	if (!var_path)
		return (NULL);
	str_cpy = ft_strdup_perm(var_path);
	if (!str_cpy)
		ft_error(ERR_MALLOC, NULL, NULL);
	i = 0;
	while (str_cpy[i] != '=')
		i++;
	str_cpy[i] = '\0';
	var_name = ft_strdup_perm(str_cpy);
	if (!var_name)
		ft_error(ERR_MALLOC, NULL, NULL);
	ft_free_perm(str_cpy);
	return (var_name);
}

void	l_add_back(t_env **l_env, char *var_name, \
	char *var_content)
{
	t_env	*list;
	t_env	*new_list;

	list = *l_env;
	while (list->next)
		list = list->next;
	new_list = ft_malloc_perm(sizeof(t_env));
	if (!new_list)
		ft_error(ERR_MALLOC, NULL, NULL);
	new_list->next = NULL;
	new_list->prev = list;
	new_list->var_name = var_name;
	new_list->var_content = var_content;
	list->next = new_list;
}
