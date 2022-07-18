/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:31:34 by mvue              #+#    #+#             */
/*   Updated: 2021/12/02 21:21:28 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*cal;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	cal = (unsigned char *)malloc(nmemb * size);
	if (!cal)
		return (NULL);
	ft_bzero(cal, nmemb * size);
	return (cal);
}
