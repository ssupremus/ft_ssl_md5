/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:06:20 by ysushkov          #+#    #+#             */
/*   Updated: 2019/07/10 17:56:52 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

uint32_t	reverse_number(uint32_t number)
{
	return ((number >> 24) | ((number & 0xff0000) >> 8) |
		((number & 0xff00) << 8) | (number << 24));
}

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

static void	print_left(t_ssl *ssl, char *hash)
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

static void	print_right(t_ssl *ssl)
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
	if (ssl->flags.p && ssl->origin == STDIN)
		ft_putstr(ssl->line);
	if (!ssl->flags.r && !ssl->flags.q)
		print_left(ssl, "MD5");
	print_block(reverse_number(ssl->a0));
	print_block(reverse_number(ssl->b0));
	print_block(reverse_number(ssl->c0));
	print_block(reverse_number(ssl->d0));
	if (ssl->flags.r && !ssl->flags.q)
		print_right(ssl);
	ft_putchar('\n');
}

void		print_sha256(t_ssl *ssl)
{
	if (ssl->flags.p && ssl->origin == STDIN)
		ft_putstr(ssl->line);
	if (!ssl->flags.r && !ssl->flags.q)
		print_left(ssl, "SHA256");
	print_block(ssl->a0);
	print_block(ssl->b0);
	print_block(ssl->c0);
	print_block(ssl->d0);
	print_block(ssl->e0);
	print_block(ssl->f0);
	print_block(ssl->g0);
	print_block(ssl->h0);
	if (ssl->flags.r && !ssl->flags.q)
		print_right(ssl);
	ft_putchar('\n');
}
