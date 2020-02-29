/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:06:20 by ysushkov          #+#    #+#             */
/*   Updated: 2020/02/24 20:08:17 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static void	print_block(uint32_t block)
{
	int		i;
	char	*buffer;

	buffer = ft_itoa_base(block, 16);
	i = ft_strlen(buffer) - 1;
	while (++i < 8)
		ft_putchar('0');
	ft_putstr(buffer);
	ft_strdel(&buffer);
}

void		print_left(t_ssl *ssl, char *hash)
{
	if (ssl->origin == STRING)
	{
		ft_putstr(hash);
		ft_putstr(" (\"");
		ft_putstr(ssl->line);
		ft_putstr("\") = ");
	}
	else if (ssl->origin == FILES)
	{
		ft_putstr(hash);
		ft_putstr(" (");
		ft_putstr(ssl->file_name);
		ft_putstr(") = ");
	}
}

void		print_right(t_ssl *ssl)
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

void		print_md5(t_ssl *ssl)
{
	if (ssl->flags.p && ssl->origin == STDIN)
		ft_putstr(ssl->line);
	if (!ssl->flags.r && !ssl->flags.q)
		print_left(ssl, "MD5");
	print_block(R(ssl->a0));
	print_block(R(ssl->b0));
	print_block(R(ssl->c0));
	print_block(R(ssl->d0));
	if (ssl->flags.r && !ssl->flags.q)
		print_right(ssl);
	ft_putchar('\n');
}

void		print_sha224256(t_ssl *ssl, char *hash)
{
	if (ssl->flags.p && ssl->origin == STDIN)
		ft_putstr(ssl->line);
	if (!ssl->flags.r && !ssl->flags.q)
		print_left(ssl, hash);
	print_block(ssl->a0);
	print_block(ssl->b0);
	print_block(ssl->c0);
	print_block(ssl->d0);
	print_block(ssl->e0);
	print_block(ssl->f0);
	print_block(ssl->g0);
	if (ft_strcmp(hash, "SHA256") == 0)
		print_block(ssl->h0);
	if (ssl->flags.r && !ssl->flags.q)
		print_right(ssl);
	ft_putchar('\n');
}
