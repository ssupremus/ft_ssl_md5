#include "libft.h"

void	ft_swapuint(unsigned int *a, unsigned int *b)
{
	unsigned int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
