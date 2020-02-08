#include "../includes/ft_ssl.h"
#include <stdio.h>

int		md5(t_ssl *ssl, int length, char **args)
{
	char *line;

	get_next_line(0, &line);

	printf("|%s|\n", line);
	return (0);
}
