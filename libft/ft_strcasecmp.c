#include "libft.h"

int		ft_strcasecmp(const char *a, const char *b)
{
	int		i;
	int		d;

	i = 0;
	d = 0;
	while (a[i] && b[i])
	{
		d = ft_tolower(a[i]) - ft_tolower(b[i]);
		if (d != 0)
			return (d);
		i++;
	}
	return (0);
}
