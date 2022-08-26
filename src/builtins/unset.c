#include "../../inc/minishell.h"

static void	rm_ele(t_env **l_env, char *var_name)
{
	t_env *list;

	list = *l_env;
	while (list->next)
	{
		if (!ft_strncmp(list->var_name, var_name, ft_strlen(var_name)))
		{
			if (!list->prev && list->next)
			{
				list->next->prev = NULL;
				*l_env = list->next;
			}
			if (!list->next && list->prev)
				list->prev->next = NULL;
			if (list->next && list->prev)
			{
				list->prev->next = list->next;
				list->next->prev = list->prev;
			}
			ft_free(list->var_name);
			list->var_name = NULL;
			ft_free(list);
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
	//check_valid_unset();
	rm_ele(&data->l_env, var_name);
}