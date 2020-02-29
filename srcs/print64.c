/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:06:20 by ysushkov          #+#    #+#             */
/*   Updated: 2020/02/24 20:08:17 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static void	print_block64(uint64_t block)
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

void		print_sha384512(t_ssl *ssl, char *hash)
{
	int i;
	int n;

	i = 0;
	n = ft_strcmp("SHA512", hash) == 0 ? 8 : 6;
	if (ssl->flags.p && ssl->origin == STDIN)
		ft_putstr(ssl->line);
	if (!ssl->flags.r && !ssl->flags.q)
		print_left(ssl, hash);
	while (i < n)
		print_block64(ssl->state[i++]);
	if (ssl->flags.r && !ssl->flags.q)
		print_right(ssl);
	ft_putchar('\n');
}
