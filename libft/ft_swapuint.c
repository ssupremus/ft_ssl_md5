/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swapuint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 14:59:40 by ysushkov          #+#    #+#             */
/*   Updated: 2018/03/27 13:55:11 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swapuint(unsigned int *a, unsigned int *b)
{
	unsigned int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
