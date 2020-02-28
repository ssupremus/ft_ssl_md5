/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:06:20 by ysushkov          #+#    #+#             */
/*   Updated: 2020/02/24 20:11:20 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int                 sha384(t_ssl *ssl, size_t length, uint8_t *line)
{
	ssl->total[0] = 0;
	ssl->total[1] = 0;
	ssl->state[0] = 0xcbbb9d5dc1059ed8;
	ssl->state[1] = 0x629a292a367cd507;
	ssl->state[2] = 0x9159015a3070dd17;
	ssl->state[3] = 0x152fecd8f70e5939;
	ssl->state[4] = 0x67332667ffc00b31;
	ssl->state[5] = 0x8eb44a8768581511;
	ssl->state[6] = 0xdb0c2e0d64f98fa7;
	ssl->state[7] = 0x47b5481dbefa4fa4;
	ssl->padded_message = malloc(128);
	ft_bzero(ssl->padded_message, 128);
	ssl->padded_message[0] = 0x80;
	sha384512_update(ssl, line, length);
	sha384512_finish(ssl);
	print_sha384512(ssl, "SHA384");
	free(ssl->padded_message);
	return (0);
}
