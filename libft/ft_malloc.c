#include "libft.h"

void	*ft_malloc(int size)
{
	void	*pointer;
	pointer = malloc(size);
	ft_garbage_collector(MALLOC, pointer);
	return (pointer);
}