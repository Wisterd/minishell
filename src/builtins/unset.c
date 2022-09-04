#include "../../inc/minishell.h"

//unset et export : que des chiffres, des lettres ou underscore 
//dans les noms de variables, pas de chiffre comme premier char

static void	rm_var(t_exec_data *data, char *var_name)
{
	t_env *list;

	list = data->l_env;
	while (list->next)
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
			ft_free_perm(list->var_name);
			list->var_name = NULL;
			ft_free_perm(list);
			return ;
		}
		list = list->next;
	}
}

static int	check_valid_unset(char *var_name)
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

static void	print_unset_error(char *arg)
{
	char	*to_write;

	write(2, "unset: '", 8);
	to_write = ft_strjoin_1free(arg, "': not a valid identifier\n");
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
			print_unset_error(tab_args[i]);
			g_exit_stat = 1;
		}
		else
			rm_var(data, tab_args[i]);
		i++;
	}
}