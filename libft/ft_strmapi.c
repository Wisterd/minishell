/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:27:13 by mvue              #+#    #+#             */
/*   Updated: 2021/12/02 23:34:59 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*sf;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	sf = (char *)malloc(len + 1);
	if (!sf)
		return (NULL);
	else
	{
		while (s[i])
		{
			sf[i] = f(i, s[i]);
			i++;
		}
		sf[i] = '\0';
		return (sf);
	}
}
