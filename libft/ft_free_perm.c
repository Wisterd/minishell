#include "libft.h"

void	ft_free_perm(void *pointer)
{
	ft_garbage_collector_perm(FREE, pointer);
	free(pointer);
}