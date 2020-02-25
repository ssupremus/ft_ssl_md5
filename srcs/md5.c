/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:06:20 by ysushkov          #+#    #+#             */
/*   Updated: 2020/02/24 20:12:34 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static uint32_t		g_s[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16,
	23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15,
	21, 6, 10, 15, 21, 6, 10, 15, 21
};

static uint32_t		g_k[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static void			md5_swap(t_ssl *ssl, int i)
{
	ssl->f = ssl->f + ssl->a + g_k[i] + ssl->m[ssl->g];
	ssl->tmp = ssl->d;
	ssl->d = ssl->c;
	ssl->c = ssl->b;
	ssl->b = ssl->b + LEFT(ssl->f, g_s[i]);
	ssl->a = ssl->tmp;
}

static void			md5_loop(t_ssl *ssl, int i)
{
	if (i < 16)
	{
		ssl->f = (ssl->b & ssl->c) | ((~ssl->b) & ssl->d);
		ssl->g = i;
	}
	else if (i < 32)
	{
		ssl->f = (ssl->d & ssl->b) | ((~ssl->d) & ssl->c);
		ssl->g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		ssl->f = ssl->b ^ ssl->c ^ ssl->d;
		ssl->g = (3 * i + 5) % 16;
	}
	else
	{
		ssl->f = ssl->c ^ (ssl->b | (~ssl->d));
		ssl->g = (7 * i) % 16;
	}
	md5_swap(ssl, i);
}

static int			variables(t_ssl *ssl, unsigned char *line, size_t length)
{
	ssl->a0 = 0x67452301;
	ssl->b0 = 0xefcdab89;
	ssl->c0 = 0x98badcfe;
	ssl->d0 = 0x10325476;
	ssl->len = length + 1;
	while (ssl->len % 64 != 56)
		ssl->len++;
	if (!(ssl->padded_message = malloc(ssl->len + 64)))
		return (-1);
	ft_bzero(ssl->padded_message, ssl->len + 64);
	ft_strcpy((char *)ssl->padded_message, (const char *)line);
	*(uint32_t *)(ssl->padded_message + length) = 0x80;
	*(uint32_t *)(ssl->padded_message + ssl->len) = (uint32_t)(8 * length);
	ssl->chunk = 0;
	return (0);
}

int					md5(t_ssl *ssl, size_t length, uint8_t *line)
{
	int i;

	if (variables(ssl, line, length) == -1)
		return (-1);
	while (ssl->chunk < ssl->len)
	{
		ssl->m = (uint32_t *)(ssl->padded_message + ssl->chunk);
		ssl->a = ssl->a0;
		ssl->b = ssl->b0;
		ssl->c = ssl->c0;
		ssl->d = ssl->d0;
		i = 0;
		while (i < 64)
			md5_loop(ssl, i++);
		ssl->a0 += ssl->a;
		ssl->b0 += ssl->b;
		ssl->c0 += ssl->c;
		ssl->d0 += ssl->d;
		ssl->chunk += 64;
	}
	free(ssl->padded_message);
	print_md5(ssl);
	return (0);
}
