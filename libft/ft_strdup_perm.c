#include "libft.h"

char	*ft_strdup_perm(const char *s1)
{
	int		len;
	char	*cp;
	int		i;

	len = ft_strlen(s1);
	cp = ft_malloc_perm(len + 1);
	i = 0;
	if (!cp)
		return (NULL);
	else
	{
		while (i < len + 1)
		{
			cp[i] = s1[i];
			i++;
		}
	}
	return (cp);
}