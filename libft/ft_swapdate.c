#include "libft.h"

void	ft_swapdate(time_t *a, time_t *b)
{
	time_t temp;

	temp = *a;
	*a = *b;
	*b = temp;
}