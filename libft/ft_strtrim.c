/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 23:46:13 by mvue              #+#    #+#             */
/*   Updated: 2021/12/04 19:33:28 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	getstart(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (ft_isinset(s1[i], set))
		i++;
	return (i);
}

static int	getend(char const *s1, char const *set, int len)
{
	int	cpt;

	cpt = 0;
	while (ft_isinset(s1[len - 1], set))
	{
		len--;
		cpt++;
	}
	return (cpt);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		nstart;
	int		nend;
	char	*st;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	nstart = getstart(s1, set);
	nend = getend(s1, set, len);
	st = ft_substr(s1, nstart, len - nstart - nend);
	return (st);
}
