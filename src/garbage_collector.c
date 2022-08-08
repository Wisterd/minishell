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

void	add_front(t_garbage **alst, void *pointer)
{
	t_garbage	*l_new;

	l_new = malloc(sizeof(t_garbage *));
	l_new->pointer = pointer; 
	if (*alst)
	{
		(*alst)->prev = l_new;
		l_new->next = *alst;
		*alst = l_new;
	}
	else
		*alst = l_new;
}

void	rm_ele(t_garbage **l_malloc, void *pointer)
{
	t_garbage *first;

	first = *l_malloc;
	while ((*l_malloc)->next)
	{
		if ((*l_malloc)->pointer == pointer)
		{
			(*l_malloc)->prev->next = (*l_malloc)->next;
			(*l_malloc)->next->prev = (*l_malloc)->prev;
			free(*l_malloc);
		}
		*l_malloc = (*l_malloc)->next;
	}
	*l_malloc = first;
}

void	garbage_collector(int mode, void *pointer)
{
	static t_garbage	*l_malloc = NULL;

	if (mode == MALLOC)
		add_front(&l_malloc, pointer);
	if (mode == FREE)
		rm_ele(&l_malloc, pointer);
	//if (mode == END)
	//	free_all(&l_malloc);
	while (l_malloc)
	{
		printf("in struct : %p\n", l_malloc->pointer);
		l_malloc = l_malloc->next;
	}
}

int	main(void)
{
	int	*test1;
	char *test2;

	test1 = ft_malloc(sizeof(int));
	test2 = ft_malloc(sizeof(char) * 5);
	printf("real test1 : %p\n", test1);
	printf("real test2 : %p\n", test2);
	ft_free(test2);
}