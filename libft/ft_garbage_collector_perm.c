#include "libft.h"

void	ft_garbage_collector_perm(int mode, void *pointer)
{
	static t_garbage	*l_garbage = NULL;
	
	if (mode == INIT)
	{
		l_garbage = malloc(sizeof(t_garbage));
		if (!l_garbage)
		{
			write(2, "Malloc error\n", 13);
			exit(1);
		}
		l_garbage->prev = NULL;
		l_garbage->next = NULL;
		l_garbage->pointer = NULL;
	}
	if (mode == MALLOC)
		add_front(&l_garbage, pointer);
	if (mode == FREE)
		rm_ele(&l_garbage, pointer);
	if (mode == END)
	{
		free_all(&l_garbage);
		free(l_garbage);
	}
}