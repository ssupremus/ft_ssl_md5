/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224256_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:06:20 by ysushkov          #+#    #+#             */
/*   Updated: 2020/02/24 20:11:20 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static uint32_t		g_k[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

void			sha224256_loop(t_ssl *ssl, int i)
{
	uint32_t s1;
	uint32_t s0;
	uint32_t ch;
	uint32_t maj;

	s1 = RIGHT(ssl->e, 6) ^ RIGHT(ssl->e, 11) ^ RIGHT(ssl->e, 25);
	ch = (ssl->e & ssl->f) ^ ((~ssl->e) & ssl->g);
	ssl->tmp = ssl->h + s1 + ch + g_k[i] + ssl->m[i];
	s0 = RIGHT(ssl->a, 2) ^ RIGHT(ssl->a, 13) ^ RIGHT(ssl->a, 22);
	maj = (ssl->a & ssl->b) ^ (ssl->a & ssl->c) ^ (ssl->b & ssl->c);
	ssl->tmp2 = s0 + maj;
	ssl->h = ssl->g;
	ssl->g = ssl->f;
	ssl->f = ssl->e;
	ssl->e = ssl->d + ssl->tmp;
	ssl->d = ssl->c;
	ssl->c = ssl->b;
	ssl->b = ssl->a;
	ssl->a = ssl->tmp + ssl->tmp2;
}

void			sha224256_schedule(t_ssl *ssl, int i)
{
	int j;

	ssl->m = malloc(512);
	ft_bzero(ssl->m, 512);
	ft_memcpy(ssl->m, &ssl->msg_32[i * 16], 16 * 32);
	j = 16;
	while (j < 64)
	{
		ssl->tmp2 = RIGHT(ssl->m[j - 15], 7) ^
		RIGHT(ssl->m[j - 15], 18) ^ (ssl->m[j - 15] >> 3);
		ssl->tmp = RIGHT(ssl->m[j - 2], 17) ^
		RIGHT(ssl->m[j - 2], 19) ^ (ssl->m[j - 2] >> 10);
		ssl->m[j] = ssl->m[j - 16] + ssl->tmp2 + ssl->m[j - 7] + ssl->tmp;
		j++;
	}
	ssl->a = ssl->a0;
	ssl->b = ssl->b0;
	ssl->c = ssl->c0;
	ssl->d = ssl->d0;
	ssl->e = ssl->e0;
	ssl->f = ssl->f0;
	ssl->g = ssl->g0;
	ssl->h = ssl->h0;
}

void			sha224256_swap(t_ssl *ssl)
{
	ssl->a0 += ssl->a;
	ssl->b0 += ssl->b;
	ssl->c0 += ssl->c;
	ssl->d0 += ssl->d;
	ssl->e0 += ssl->e;
	ssl->f0 += ssl->f;
	ssl->g0 += ssl->g;
	ssl->h0 += ssl->h;
}
