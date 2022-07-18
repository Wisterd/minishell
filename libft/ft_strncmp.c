/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 19:05:42 by mvue              #+#    #+#             */
/*   Updated: 2021/12/02 13:49:53 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	else
	{
		while (s1[i] == s2[i] && s1[i] && s2[i] && n - 1 > i)
			i ++;
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		else
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
	}
}
