/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 19:05:42 by mvue              #+#    #+#             */
/*   Updated: 2022/07/28 02:24:15 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (!s1 || !s2)
		return (-1);
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
