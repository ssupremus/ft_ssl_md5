#include "libft.h"

void	ft_swapstr(char **a, char **b)
{
	char *temp;

	temp = *a;
	*a = *b;
	*b = temp;
}