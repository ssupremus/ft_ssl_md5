#include "../includes/ft_ssl.h"

static void print_block64(uint64_t block)
{
	int		i;
	char	*buffer;

	buffer = uint64_itoa_base(block, 16);
	i = ft_strlen(buffer) - 1;
	while (++i < 16)
		ft_putchar('0');
	ft_putstr(buffer);
	ft_strdel(&buffer);
}

void		print_sha512(t_ssl *ssl)
{
    int i;

    i = 0;
	if (ssl->flags.p && ssl->origin == STDIN)
		ft_putstr(ssl->line);
	if (!ssl->flags.r && !ssl->flags.q)
		print_left(ssl, "SHA512");
    while (i < 8)
	    print_block64(ssl->state[i++]);
	if (ssl->flags.r && !ssl->flags.q)
		print_right(ssl);
	ft_putchar('\n');
}