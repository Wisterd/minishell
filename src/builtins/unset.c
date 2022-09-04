#include "../../inc/minishell.h"

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

/*
void	check_valid_unset(t_exec_data *data)
{

}
*/

void	ft_unset(t_exec_data *data, char *var_name)
{
	if (!data->tab_parse[data->ind_cmd].tab_args[1])
		return ;
	//check_valid_unset();
	rm_var(data, var_name);
}