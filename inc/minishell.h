#ifndef MINISELL_H
# define MINISELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

#define MALLOC 0
#define FREE 1
#define END 2

typedef struct s_garbage
{
	void				*pointer;
	struct s_garbage	*next;
	struct s_garbage	*prev;
}	t_garbage;

void	*ft_malloc(int size);
void	garbage_collector(int mode, void *pointer);
void	add_front(t_garbage **alst, void *pointer);
void	rm_ele(t_garbage **l_malloc, void *pointer);

#endif