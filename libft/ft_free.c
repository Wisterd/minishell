#include "libft.h"

void	ft_free(void *pointer)
{
	ft_garbage_collector(FREE, pointer);
	free(pointer);
}