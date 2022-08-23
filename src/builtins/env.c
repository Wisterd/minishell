#include "../../inc/minishell.h"

t_env	*init_env(char	**envp)
{
	t_env	*my_env;
	char	*start_env;

	my_env = ft_malloc(sizeof(t_env));
	my_env->next = NULL;

}