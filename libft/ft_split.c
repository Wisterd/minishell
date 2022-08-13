/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:03:22 by mvue              #+#    #+#             */
/*   Updated: 2021/12/03 00:58:03 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countword(char const *s, char c)
{
	int	i;
	int	len;
	int	cptword;

	i = 0;
	len = ft_strlen(s);
	cptword = 0;
	while (s[i])
	{
		if (s[i] != c && s[i + 1] == c)
			cptword++;
		i++;
	}
	if (len && s[len - 1] != c)
		cptword++;
	if (c == '\0')
		cptword--;
	return (cptword);
}

static int	ft_getstr(char const *s, char c, int *istr)
{
	int	lenstr;
	int	i;

	lenstr = 0;
	while (s[*istr] == c && s[*istr])
		*istr += 1;
	i = *istr;
	while (s[i] != c && s[i])
	{
		lenstr++;
		i++;
	}
	return (lenstr);
}

char	**ft_split(char const *s, char c)
{
	int		nbword;
	int		lenstr;
	char	**tab;
	int		itab;
	int		istr;

	nbword = ft_countword(s, c);
	tab = ft_malloc((nbword + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	if (!*s)
	{
		tab[0] = NULL;
		return (tab);
	}
	itab = -1;
	istr = 0;
	tab[nbword] = NULL;
	while (++itab < nbword)
	{
		lenstr = ft_getstr(s, c, &istr);
		tab[itab] = ft_substr(s, istr, lenstr);
		istr += lenstr;
	}
	return (tab);
}
