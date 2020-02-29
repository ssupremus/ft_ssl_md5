/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:06:20 by ysushkov          #+#    #+#             */
/*   Updated: 2020/02/24 20:11:20 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int		sha512(t_ssl *ssl, size_t length, uint8_t *line)
{
	ssl->total[0] = 0;
	ssl->total[1] = 0;
	ssl->state[0] = 0x6a09e667f3bcc908;
	ssl->state[1] = 0xbb67ae8584caa73b;
	ssl->state[2] = 0x3c6ef372fe94f82b;
	ssl->state[3] = 0xa54ff53a5f1d36f1;
	ssl->state[4] = 0x510e527fade682d1;
	ssl->state[5] = 0x9b05688c2b3e6c1f;
	ssl->state[6] = 0x1f83d9abfb41bd6b;
	ssl->state[7] = 0x5be0cd19137e2179;
	ssl->padded_message = malloc(128);
	ft_bzero(ssl->padded_message, 128);
	ssl->padded_message[0] = 0x80;
	sha384512_update(ssl, line, length);
	sha384512_finish(ssl);
	print_sha384512(ssl, "SHA512");
	free(ssl->padded_message);
	return (0);
}
