/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_collector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:27:58 by mvue              #+#    #+#             */
/*   Updated: 2022/09/12 19:28:52 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_all(t_garbage **l_garbage)
{
	t_garbage	*tmp_next;

	while (*l_garbage)
	{
		tmp_next = (*l_garbage)->next;
		free((*l_garbage)->pointer);
		free(*l_garbage);
		*l_garbage = tmp_next;
	}
}

void	add_front(t_garbage **l_garbage, void *pointer)
{
	t_garbage	*l_new;

	l_new = malloc(sizeof(t_garbage));
	if (!l_new)
	{
		free_all(l_garbage);
		exit(1);
	}
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
	t_garbage	*list;

	list = *l_garbage;
	while (list)
	{
		if (list->pointer == pointer)
		{
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
			list->pointer = NULL;
			free(list);
			return ;
		}
		list = list->next;
	}
}

void	ft_garbage_collector(int mode, void *pointer)
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
