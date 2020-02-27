/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:06:20 by ysushkov          #+#    #+#             */
/*   Updated: 2020/02/24 20:03:34 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

size_t	file_length(char *name)
{
	int fd;
	int ret;
	int buf[2];
	size_t length;

	fd = open(name, O_RDONLY);
	buf[1] = 0;
	length = 0;
	if (fd < 0)
		return (-1);
	while ((ret = read(fd, buf, 1)) > 0)
		length++;
	close(fd);
	return (length);
}

int	file_exists(char *name)
{
	int		fd;
	char	*buf[2];
	int		ret;

	buf[1] = 0;
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		if (errno == EACCES)
			return (-3);
		return (-1);
	}
	ret = read(fd, buf, 1); 
	close(fd);
	if (ret < 0)
		return (-2);
	return (fd);
}

char		*reading(char *name, size_t length)
{
	int fd;
	int ret;
	int buf[2];
	char *line;
	int i;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	buf[1] = 0;
	line = (char *)malloc(sizeof(char) * (length + 1));
	if (line == NULL)
		return (NULL);
	line[length] = 0;
	i = 0;
	ret = read(fd, line, length);
	close(fd);
	return (line);
}