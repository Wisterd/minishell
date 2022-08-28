/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:13:41 by mvue              #+#    #+#             */
/*   Updated: 2022/08/28 22:20:23 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_calclen(long int *nb, int *isneg)
{
	int	len;
	int	n;

	n = *nb;
	len = 0;
	if (n == 0)
		len++;
	if (*nb < 0)
	{
		*isneg = 1;
		*nb = -(*nb);
		len += 1;
	}
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long int	nb;
	char		*str;
	int			len;
	int			isneg;

	nb = n;
	isneg = 0;
	len = ft_calclen(&nb, &isneg);
	str = (char *)ft_malloc(len + sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	while (len--)
	{
		str[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (isneg)
		str[len + 1] = '-';
	return (str);
}
