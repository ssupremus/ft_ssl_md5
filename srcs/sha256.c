/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:06:20 by ysushkov          #+#    #+#             */
/*   Updated: 2020/02/24 20:11:20 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static int	variables(t_ssl *ssl, unsigned char *line, size_t length)
{
	int i;

	ssl->a0 = 0x6a09e667;
	ssl->b0 = 0xbb67ae85;
	ssl->c0 = 0x3c6ef372;
	ssl->d0 = 0xa54ff53a;
	ssl->e0 = 0x510e527f;
	ssl->f0 = 0x9b05688c;
	ssl->g0 = 0x1f83d9ab;
	ssl->h0 = 0x5be0cd19;
	ssl->len_bit = length * 8;
	ssl->chunk = 1 + ((ssl->len_bit + 16 + 64) / 512);
	if (!(ssl->msg_32 = malloc(16 * ssl->chunk * 4)))
		return (-1);
	ft_bzero(ssl->msg_32, 16 * ssl->chunk * 4);
	ft_memcpy((char *)ssl->msg_32, line, length);
	((char*)ssl->msg_32)[length] = 0x80;
	i = -1;
	while (++i < (ssl->chunk * 16) - 1)
		ssl->msg_32[i] = R(ssl->msg_32[i]);
	ssl->msg_32[((ssl->chunk * 512 - 64) / 32) + 1] = ssl->len_bit;
	return (0);
}

int			sha256(t_ssl *ssl, size_t length, uint8_t *line)
{
	int i;
	int j;

	i = 0;
	if (variables(ssl, line, length) == -1)
		return (-1);
	while (i < ssl->chunk)
	{
		sha224256_schedule(ssl, i);
		j = 0;
		while (j < 64)
			sha224256_loop(ssl, j++);
		sha224256_swap(ssl);
		free(ssl->m);
		i++;
	}
	print_sha224256(ssl, "SHA256");
	free(ssl->msg_32);
	return (0);
}
