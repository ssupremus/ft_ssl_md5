/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swapdate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 14:59:40 by ysushkov          #+#    #+#             */
/*   Updated: 2018/03/27 13:55:11 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swapdate(time_t *a, time_t *b)
{
	time_t temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
