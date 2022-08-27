#include "../inc/minishell.h"

int g_exit_stat = 0;

int main(){
	char		*prompt;
	// t_exec_data	data;

	signals();
	prompt = NULL;
	mini_exit(prompt);
}
