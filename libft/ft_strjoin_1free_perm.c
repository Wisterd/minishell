/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_1free_perm.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:33:07 by mvue              #+#    #+#             */
/*   Updated: 2022/09/12 19:33:08 by mvue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_1free_perm(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	s3 = (char *)ft_malloc_perm(ft_strlen(s1) + ft_strlen(s2) + sizeof(char));
	i = -1;
	j = 0;
	if (!s3)
		return (NULL);
	else
	{
		while (s1[++i])
			s3[i] = s1[i];
		while (s2[j])
			s3[i++] = s2[j++];
		s3[i] = '\0';
		ft_free_perm(s1);
		return (s3);
	}
}
