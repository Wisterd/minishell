#include "libft.h"

void	*ft_malloc_perm(int size)
{
	void	*pointer;
	pointer = malloc(size);
	ft_garbage_collector_perm(MALLOC, pointer);
	return (pointer);
}