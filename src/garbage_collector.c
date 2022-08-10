#include "../inc/minishell.h"

void	*ft_malloc(int size)
{
	void	*pointer;
	pointer = malloc(size);
	garbage_collector(MALLOC, pointer);
	return (pointer);
}

void	ft_free(void *pointer)
{
	garbage_collector(FREE, pointer);
	free(pointer);
}

void	add_front(t_garbage **l_garbage, void *pointer)
{
	t_garbage	*l_new;

	l_new = malloc(sizeof(t_garbage));
	l_new->prev = NULL;
	l_new->pointer = pointer; 
	if (*l_garbage)
	{
		(*l_garbage)->prev = l_new;
		l_new->next = *l_garbage;
		*l_garbage = l_new;
	}
	else
		*l_garbage = l_new;
}

void	rm_ele(t_garbage **l_garbage, void *pointer)
{
	t_garbage *list;

	list = *l_garbage;
	while (list)
	{
		if (list->pointer == pointer)
		{
			printf("freeing : %p\n", list->pointer);
			if (!list->prev && list->next)
			{
				list->next->prev = NULL;
				*l_garbage = list->next;
			}
			if (!list->next && list->prev)
				list->prev->next = NULL;
			if (list->next && list->prev)
			{
				list->prev->next = list->next;
				list->next->prev = list->prev;
			}
			free(list);
		}
		list = list->next;
	}
}

void	garbage_collector(int mode, void *pointer)
{
	static t_garbage	*l_garbage = NULL;
	t_garbage			*first;
	
	if (mode == MALLOC)
		add_front(&l_garbage, pointer);
	if (mode == FREE)
		rm_ele(&l_garbage, pointer);
	//if (mode == END)
	//	free_all(&l_garbage);
	if (mode == 9)
	{
		first = l_garbage;
		while (l_garbage)
		{
			printf("prev : %p\n", l_garbage->prev);
			printf("pointer : %p\n", l_garbage->pointer);
			printf("next : %p\n", l_garbage->next);
			l_garbage = l_garbage->next;
		}
		l_garbage = first;
	}
}

int	main(void)
{
	int	*test1;
	char *test2;

	test1 = ft_malloc(sizeof(int));
	test2 = ft_malloc(sizeof(char) * 5);
	garbage_collector(9, NULL);
	printf("real test1 : %p\n", test1);
	printf("real test2 : %p\n", test2);
	ft_free(test1);
	ft_free(test2);
	//garbage_collector(9, NULL);
}