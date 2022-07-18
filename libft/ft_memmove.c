/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:11:38 by mvue              #+#    #+#             */
/*   Updated: 2021/11/30 20:46:41 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	unsigned const char	*psrc;
	size_t				i;

	pdest = (unsigned char *) dest;
	psrc = (unsigned const char *) src;
	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			pdest[i] = psrc[i];
			i++;
		}
	}
	if (dest > src)
	{
		while (n--)
			pdest[n] = psrc[n];
	}
	return (dest);
}
