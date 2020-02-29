/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 14:59:40 by ysushkov          #+#    #+#             */
/*   Updated: 2018/03/27 13:55:11 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_length(uint64_t n, int base)
{
	int i;

	i = 0;
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

static char	*free_str(char *str)
{
	char *tmp;

	tmp = str;
	str = ft_strsub(str, 1, ft_strlen(str) - 1);
	ft_strdel(&tmp);
	return (str);
}

char		*uint64_itoa_base(uint64_t n, int base)
{
	int		i;
	int		length;
	char	*str;
	char	*chars;

	i = 0;
	chars = "0123456789abcdef";
	length = number_length(n, base);
	if (n == 0)
		return (ft_strdup("0"));
	str = (char *)malloc(sizeof(char) * (length + 1));
	if (str == NULL)
		return (NULL);
	str[length + 1] = 0;
	while (length + 1)
	{
		str[length] = chars[n % base];
		n = n / base;
		length--;
	}
	if (str[0] == '0')
		str = free_str(str);
	return (str);
}
