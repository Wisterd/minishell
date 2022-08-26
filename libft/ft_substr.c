/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:27:33 by mvue              #+#    #+#             */
/*   Updated: 2021/12/02 23:35:51 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	lenstart;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	lenstart = ft_strlen(s + start);
	if (len > lenstart)
		len = lenstart;
	sub = ft_malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (s[++i])
	{
		if (j < len && i >= start)
		{
			sub[j] = s[i];
			j++;
		}
	}
	sub[j] = '\0';
	return (sub);
}
