/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_deldeb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:47:15 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/08 18:31:46 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_str_deldeb(char *str, int len)
{
	int		i;
	char	*cp;

	i = 0;
	cp = ft_malloc((ft_strlen(str) + 1) * sizeof(char));
	while (str[i + len])
	{
		cp[i] = str[i + len];
		i++;
	}
	cp[i] = '\0';
	return (cp);
}