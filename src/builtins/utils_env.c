#include "../../inc/minishell.h"

char	*get_var_content(char *var_path)
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
	str_cpy = ft_strdup(var_path);
	if (!str_cpy)
		ft_error(ERR_MALLOC, NULL, NULL);
	i = 0;
	while (str_cpy[i] != '=')
		i++;
	str_cpy[i] = '\0';
	var_name = ft_strdup(str_cpy);
	if (!var_name)
		ft_error(ERR_MALLOC, NULL, NULL);
	ft_free(str_cpy);
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
	new_list = ft_malloc(sizeof(t_env));
	if (!new_list)
		ft_error(ERR_MALLOC, NULL, NULL);
	new_list->next = NULL;
	new_list->prev = list;
	new_list->var_name = var_name;
	new_list->var_content = var_content;
	list->next = new_list;
}
