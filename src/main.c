#include "../inc/minishell.h"

int main()
{
	char		*prompt;
	t_exec_data	data;

	ft_garbage_collector(INIT, NULL);
	signals();
	prompt = NULL;
	mini_exit(prompt, &data);
}
