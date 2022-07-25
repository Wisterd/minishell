/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:27:40 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/25 18:31:00 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strldup(const char *s1, size_t size)
{
	int		len;
	char	*cp;
	int		i;

	if (!size)
		return (NULL);
	len = ft_strlen(s1);
	cp = (char *)malloc(len + 1);
	i = 0;
	if (!cp)
		return (NULL);
	else
	{
		while (i < len + 1 && i < size)
		{
			cp[i] = s1[i];
			i++;
		}
	}
	return (cp);
}
