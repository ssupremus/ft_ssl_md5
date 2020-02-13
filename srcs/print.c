#include "../includes/ft_ssl.h"
#include <stdio.h>

uint32_t	reverse_number(uint32_t n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) |
		((n & 0xff00) << 8) | (n << 24));
}

char		*add0(char *str)
{
	int i;

	i = ft_strlen(str);
	while (i < 8)
	{
		ft_putchar('0');
		i++;
	}
	return (str);
}

void	print_left(t_ssl *ssl)
{
	if (ssl->origin == STRING)
	{
		ft_putstr("MD5 (\"");
		ft_putstr(ssl->line);
		ft_putstr("\") = ");
	}
	else if (ssl->origin == FILES)
	{
		ft_putstr("MD5 (");
		ft_putstr(ssl->file_name);
		ft_putstr(") = ");
	}
}

void	print_right(t_ssl *ssl)
{
	if (ssl->origin == STRING)
	{
		ft_putstr(" \"");
    ft_putstr(ssl->line);
		ft_putstr("\"");
	}
  else if (ssl->origin == FILES)
  {
    ft_putchar(' ');
		ft_putstr(ssl->file_name);
  }
}

void  print_md5(t_ssl *ssl)
{
	char *t;

	if (ssl->flags.p && ssl->origin == STDIN)
		ft_putstr(ssl->line);
	if (!ssl->flags.r && !ssl->flags.q)
		print_left(ssl);
	t = ft_itoa_base(reverse_number(ssl->a0), 16);
	add0(t);
	ft_putstr(t);
	free(t);
	t = ft_itoa_base(reverse_number(ssl->b0), 16);
	add0(t);
	ft_putstr(t);
	free(t);
	t = ft_itoa_base(reverse_number(ssl->c0), 16);
	add0(t);
	ft_putstr(t);
	free(t);
	t = ft_itoa_base(reverse_number(ssl->d0), 16);
	add0(t);
	ft_putstr(t);
	if (ssl->flags.r && !ssl->flags.q)
		print_right(ssl);
	ft_putchar('\n');
	free(t);
}
