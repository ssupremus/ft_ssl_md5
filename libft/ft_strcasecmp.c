/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasecmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 14:59:40 by ysushkov          #+#    #+#             */
/*   Updated: 2018/03/27 13:55:11 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcasecmp(const char *a, const char *b)
{
	int		i;
	int		d;

	i = 0;
	d = 0;
	while (a[i] && b[i])
	{
		d = ft_tolower(a[i]) - ft_tolower(b[i]);
		if (d != 0)
			return (d);
		i++;
	}
	return (0);
}
