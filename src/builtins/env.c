#include "../../inc/minishell.h"

/*
static void	rm_ele(t_garbage **l_env, void *pointer)
{
	t_garbage *list;

	list = *l_env;
	while (list)
	{
		if (list->pointer == pointer)
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
			list->pointer = NULL;
			free(list);
			return ;
		}
		list = list->next;
	}
}
*/

static void	l_add_back(t_env **l_env, char *var_name, \
	char *var_content, t_exec_data *data)
{
	t_env	*list;
	t_env	*new_list;

	list = *l_env;
	while (list->next)
		list = list->next;
	new_list = ft_malloc(sizeof(t_env));
	if (!new_list)
		ft_error(ERR_MALLOC, NULL, data->pipes);
	new_list->next = NULL;
	new_list->prev = list;
	new_list->var_name = var_name;
	new_list->var_content = var_content;
	list->next = new_list;
}

static char	*get_var_content(t_exec_data *data, char *var_path)
{
	char	*var_content;

	if (!var_path)
		return (NULL);
	while (*var_path != '=')
		var_path++;
	var_path++;
	if (!*var_path)
		var_content = ft_strdup("");
	else
		var_content = ft_strdup(var_path);
	if (!var_content)
		ft_error(ERR_MALLOC, NULL, data->pipes);
	return (var_content);
}

static char	*get_var_name(t_exec_data *data, char *var_path)
{
	char	*var_name;
	char	*str_cpy;
	int		i;

	if (!var_path)
		return (NULL);
	str_cpy = ft_strdup(var_path);
	if (!str_cpy)
		ft_error(ERR_MALLOC, NULL, data->pipes);
	i = 0;
	while (str_cpy[i] != '=')
		i++;
	str_cpy[i] = '\0';
	var_name = ft_strdup(str_cpy);
	if (!var_name)
		ft_error(ERR_MALLOC, NULL, data->pipes);
	ft_free(str_cpy);
	return (var_name);
}

t_env	*init_env(t_exec_data *data, char **envp)
{
	t_env	*l_env;
	int		i;

	i = 0;
	l_env = ft_malloc(sizeof(t_env));
	if (!l_env)
		ft_error(ERR_MALLOC, NULL, data->pipes);
	l_env->var_content = ft_strdup(ft_getcwd(data));
	l_env->var_name = ft_strdup("?PWD");
	l_env->next = NULL;
	l_env->prev = NULL;
	while (envp[i++])
	{
		l_add_back(&l_env, get_var_name(data, envp[i]), \
			get_var_content(data, envp[i]), data);
	}
	return (l_env);
}

void	print_env(t_env *l_env)
{
	while (l_env)
	{
		if (l_env->var_name && ft_strncmp("?", l_env->var_name, 1))
			printf("%s=%s\n", l_env->var_name, l_env->var_content);
		l_env = l_env->next;
	}
}

int	main(int ac, char **av, char *envp[])
{
	t_exec_data	data;
	t_env		*l_env;
	(void)		ac;
	(void)		av;

	ft_garbage_collector(INIT, NULL);
	data.n_cmds = 4;
	data.pipes = init_pipes(&data);
	l_env = init_env(&data, envp);
	print_env(l_env);
	ft_garbage_collector(END, NULL);
}