/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 19:05:27 by mvue              #+#    #+#             */
/*   Updated: 2022/08/29 19:06:25 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	else
	{
		while (s1[i] == s2[i] && s1[i] && s2[i] && s1[i] && s2[i])
			i ++;
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		else
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
	}
}
