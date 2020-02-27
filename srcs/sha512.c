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

static uint64_t        g_k[] =
{
	0x428a2f98d728ae22, 0x7137449123ef65cd,
	0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
	0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe,
	0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
	0x9bdc06a725c71235, 0xc19bf174cf692694,
	0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
	0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210,
	0xb00327c898fb213f, 0xbf597fc7beef0ee4,
	0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926,
	0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8,
	0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30,
	0xd192e819d6ef5218, 0xd69906245565a910,
	0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
	0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc, 0x78a5636f43172f60,
	0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9,
	0xbef9a3f7b2c67915, 0xc67178f2e372532b,
	0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6,
	0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493,
	0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
	0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

void    get_uint64_be(uint64_t *n, const unsigned char *b, int i)
{
	*n = ((uint64_t)(b)[(i)] << 56) | \
		((uint64_t)(b)[(i) + 1] << 48) | \
		((uint64_t)(b)[(i) + 2] << 40) | \
		((uint64_t)(b)[(i) + 3] << 32) | \
		((uint64_t)(b)[(i) + 4] << 24) | \
		((uint64_t)(b)[(i) + 5] << 16) | \
		((uint64_t)(b)[(i) + 6] << 8) | \
		((uint64_t)(b)[(i) + 7]);
}

void     put_uint64_be(uint64_t n, unsigned char *b, int i)
{
	(b)[(i)] = (unsigned char)((n) >> 56);
	(b)[(i) + 1] = (unsigned char)((n) >> 48);
	(b)[(i) + 2] = (unsigned char)((n) >> 40);
	(b)[(i) + 3] = (unsigned char)((n) >> 32);
	(b)[(i) + 4] = (unsigned char)((n) >> 24);
	(b)[(i) + 5] = (unsigned char)((n) >> 16);
	(b)[(i) + 6] = (unsigned char)((n) >> 8);
	(b)[(i) + 7] = (unsigned char)((n));
}

static void sha512_swap(t_ssl *ssl, int i)
{
	int mem;
	int k;
	int j;
	int m[8];
	uint64_t temp1;
	uint64_t temp2;

	k = 0;
	mem = 8 - (i % 8);
	j = mem;
	while (j < 8)
		m[k++] = j++;
	if (mem != 0)
	{
		j = 0;
		while (j < mem)
		m[k++] = j++;
	}
	temp1 = ssl->hh[m[7]] + S3(ssl->hh[m[4]]) + F1(ssl->hh[m[4]], ssl->hh[m[5]], ssl->hh[m[6]]) + g_k[i] + ssl->w[i];
	temp2 = S2(ssl->hh[m[0]]) + F0(ssl->hh[m[0]], ssl->hh[m[1]], ssl->hh[m[2]]);
	ssl->hh[m[3]] += temp1;
	ssl->hh[m[7]] = temp1 + temp2;
}

static void sha512_process(t_ssl *ssl, const unsigned char data[128])
{
	int i;

	i = -1;
	while (++i < 16)
		get_uint64_be(&ssl->w[i], data, i << 3);
	i = 15;
	while (++i < 80)
		ssl->w[i] = S1(ssl->w[i - 2]) + ssl->w[i - 7] + S0(ssl->w[i - 15]) + ssl->w[i - 16];
	i = -1;
	while (++i < 8)
		ssl->hh[i] = ssl->state[i];
	i = 0;
	while (i < 80)
		sha512_swap(ssl, i++);
	i = -1;
	while (++i < 8)
		ssl->state[i] += ssl->hh[i];
}

static void sha512_update(t_ssl *ssl, const unsigned char *input, size_t length)
{
	unsigned int left;

	if (length == 0)
		return ;
	left = (unsigned int)(ssl->total[0] & 0x7F);
	ssl->len_bit = 128 - left;
	ssl->total[0] += (uint64_t)length;
	if (ssl->total[0] < (uint64_t)length)
		ssl->total[1]++;
	if (left && length >= ssl->len_bit)
	{
		ft_memcpy((void *)(ssl->buffer + left), input, ssl->len_bit);
		sha512_process(ssl, ssl->buffer);
		input += ssl->len_bit;
		length -= ssl->len_bit;
		left = 0;
	}
	while (length >= 128)
	{
		sha512_process(ssl, input);
		input += 128;
		length -= 128;
	}
	if (length > 0)
		ft_memcpy((void *)(ssl->buffer + left), input, length);
}

static void sha512_finish(t_ssl *ssl)
{
	size_t      last;
	size_t      padn;
	uint64_t    high;
	uint64_t    low;

	unsigned char msglen[16];
	high = (ssl->total[0] >> 61) | (ssl->total[1] << 3);
	low = (ssl->total[0] << 3);
	put_uint64_be(high, msglen, 0);
	put_uint64_be(low, msglen, 8);
	last = (size_t)(ssl->total[0] & 0x7F);
	padn = (last < 112) ? (112 - last) : (240 - last);
	sha512_update(ssl, ssl->padded_message, padn);
	sha512_update(ssl, msglen, 16);
}

int                 sha512(t_ssl *ssl, size_t length, uint8_t *line)
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
	sha512_update(ssl, line, length);
	sha512_finish(ssl);
	print_sha512(ssl);
	free(ssl->padded_message);
	return (0);
}
