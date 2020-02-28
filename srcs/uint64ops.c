/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384512_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:06:20 by ysushkov          #+#    #+#             */
/*   Updated: 2020/02/24 20:11:20 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

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