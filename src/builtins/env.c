#include "../../inc/minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*l_env;
	int		i;

	i = 0;
	l_env = ft_malloc_perm(sizeof(t_env));
	if (!l_env)
		ft_error(ERR_MALLOC, NULL, NULL);
	l_env->var_content = ft_strdup_perm(ft_getcwd_perm());
	l_env->var_name = ft_strdup_perm("?PWD");
	l_env->next = NULL;
	l_env->prev = NULL;
	while (envp[i])
	{
		l_add_back(&l_env, get_var_name(envp[i]), \
			get_var_content(envp[i]));
		i++;
	}
	return (l_env);
}

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

char	**ft_get_total_env(t_exec_data *data)
{
	char	**tab_env;
	t_env	*list;
	int		i;

	i = 0;
	list = data->l_env;
	while (list)
	{
		i++;
		list = list->next;
	}	
	tab_env = ft_malloc(sizeof(char *) * (i + 1));
	list = data->l_env;
	i = 0;
	while (list->next)
	{
		tab_env[i] = ft_strjoin(list->var_name, "=");
		if (!tab_env[i])
			ft_error(ERR_MALLOC, NULL, data->pipes);
		tab_env[i] = ft_strjoin(tab_env[i], list->var_content);
		if (!tab_env[i])
			ft_error(ERR_MALLOC, NULL, data->pipes);
		i++;
		list = list->next;
	}
	tab_env[i] = NULL;
	return (tab_env);
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
			if (data->l_env->var_name && ft_strncmp("?", data->l_env->var_name, 1))
			{
				if (protected_putstr(data->l_env->var_name, "env", data) == -1)
					return ;
				protected_putstr("=", "env", data);
				protected_putstr(data->l_env->var_content, "env", data);
				protected_putstr("\n", "env", data);
			}
			data->l_env = data->l_env->next;
		}
		data->l_env = start_list;
		g_exit_stat = 0;
	}
}

/*
int	main(int ac, char **av, char *envp[])
{
	t_exec_data	data;
	(void)		ac;
	(void)		av;

	ft_garbage_collector(INIT, NULL);
	data.n_cmds = 4;
	data.pipes = init_pipes(&data);
	data.l_env = init_env(&data, envp);
	ft_unset(&data, "ZDOTDIR");
	ft_env(&data);
	ft_garbage_collector(END, NULL);
}
*/