/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:32:17 by mvue              #+#    #+#             */
/*   Updated: 2022/09/12 19:32:38 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(int size)
{
	void	*pointer;

	pointer = malloc(size);
	if (!pointer)
		return (NULL);
	ft_garbage_collector(MALLOC, pointer);
	return (pointer);
}
