/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_perm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:32:47 by mvue              #+#    #+#             */
/*   Updated: 2022/09/12 19:32:55 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc_perm(int size)
{
	void	*pointer;

	pointer = malloc(size);
	if (!pointer)
		return (NULL);
	ft_garbage_collector_perm(MALLOC, pointer);
	return (pointer);
}
