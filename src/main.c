#include "../inc/minishell.h"

int main(int ac, char **av, char **envp)
{
	char		*prompt;
	t_exec_data	data;
	(void)		ac;
	(void)		av;
	
	ft_garbage_collector_perm(INIT, NULL);
	data.l_env = init_env(envp);
	signals();
	prompt = NULL;
	mini_exit(prompt, &data);
}

/*
int main(int ac, char **av, char **envp)
{
	t_exec_data	data;
	char		**tab_env;
	(void)		ac;
	(void)		av;
	int			i;

	ft_garbage_collector(INIT, NULL);
	data.l_env = init_env(envp);
	data.pipes = NULL;
	tab_env = ft_get_total_env(&data);
	i = 0;
	while (tab_env[i])
	{
		printf("%s\n", tab_env[i]);
		i++;
	}
	ft_garbage_collector(END, NULL);
}
*/