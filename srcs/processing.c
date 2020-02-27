/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:06:20 by ysushkov          #+#    #+#             */
/*   Updated: 2020/02/24 20:03:34 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void		flags(t_ssl *ssl, int argc, char **argv)
{
	int	i;

	i = 1;
	while (++i < argc)
	{
		if (ft_strcmp(argv[i], "-p") == 0)
			ssl->flags.p = 1;
		else if (ft_strcmp(argv[i], "-q") == 0)
			ssl->flags.q = 1;
		else if (ft_strcmp(argv[i], "-r") == 0)
			ssl->flags.r = 1;
		else if (ft_strcmp(argv[i], "-s") == 0)
		{
			ssl->flags.s = 1;
			if (i < (argc - 1))
				ssl->string_index = i + 1;
			i++;
		}
		else
		{
			ssl->file_index = i;
			break ;
		}
	}
}

// static void	send_line(t_ssl *ssl, char **args)
// {
// 	if (ft_strcmp(args[1], "md5") == 0)
// 		md5(ssl, ft_strlen(ssl->line), (uint8_t *)ssl->line);
// 	else if (ft_strcmp(args[1], "sha256") == 0)
// 		sha256(ssl, ft_strlen(ssl->line), (uint8_t *)ssl->line);
// }

static size_t	file_length(char *name)
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

#include <stdio.h>

char		*sieg_heil(char *name, size_t length)
{
	int fd;
	int ret;
	int buf[2];
	char *line;
	int i;

	fd = open(name, O_RDONLY);
	buf[1] = 0;
	line = (char *)malloc(sizeof(char) * (length + 1));
	if (line == NULL)
		return (NULL);
	line[length] = 0;
	i = 0;
	//while ((ret = read(fd, buf, 1)) > 0)
//		line[i++] = buf[0];
	ret = read(fd, line, length);
	close(fd);
	return (line);
}

static void	read_file(t_ssl *ssl, char **args, int index)
{
	//int		fd;
	char	*line;
	size_t	length;

	line = NULL;
	length = 0;
	ssl->file_name = ft_strdup(args[index]);
	length = file_length(ssl->file_name);
	printf("%i\n", (int)length);
	ssl->line = sieg_heil(ssl->file_name, length);
	if (ft_strcmp("md5", args[1]) == 0)
		md5(ssl, length, (uint8_t *)ssl->line);
	else
		sha256(ssl, length, (uint8_t *)ssl->line);
	//printf("%s", line);
	//ft_strdel(&line);
	//fd = open(ssl->file_name, O_RDONLY);
	// if (fd != -1)
	// {
	// 	if (get_next_line(fd, &line) == -1)
	// 		read_error(ssl->file_name, args[1]);
	// 	else
	// 	{
	// 		ssl->line = ft_strdup(line);
	// 		send_line(ssl, args);
	// 		if (line != NULL)
	// 		{
	// 			ft_strdel(&line);
	ft_strdel(&ssl->line);
	// 		}
	// 	}
	// 	close(fd);
	// }
	// else
	// 	no_such_file(ssl->file_name, args[1]);
	ft_strdel(&ssl->file_name);
}

static void	read_string(t_ssl *ssl, int argc, char **args)
{
	int i;

	i = 1;
	ssl->origin = STRING;
	while (++i < argc)
	{
		if (i < ssl->string_index && ft_strcmp(args[i], "-s") == 0)
		{
			ssl->line = ft_strdup(args[i + 1]);
			if (ft_strcmp(args[1], "md5") == 0)
				md5(ssl, ft_strlen(ssl->line), (uint8_t *)ssl->line);
			else if (ft_strcmp(args[1], "sha256") == 0)
				sha256(ssl, ft_strlen(ssl->line), (uint8_t *)ssl->line);
			ft_strdel(&ssl->line);
		}
		else if ((i + 1) == argc && ft_strcmp(args[i], "-s") == 0 &&
				!ssl->file_index)
			string_error(args[1]);
	}
}

void		processing(t_ssl *ssl, int argc, char **args)
{
	char	*line;

	line = NULL;
	flags(ssl, argc, args);
	if (ssl->flags.p || (!ssl->flags.s && !ssl->file_index))
	{
		ssl->origin = STDIN;
		get_next_line(STDIN, &line);
		ssl->line = ft_strdup(line);
		if (ft_strcmp(args[1], "md5") == 0)
			md5(ssl, ft_strlen(ssl->line), (uint8_t *)ssl->line);
		else if (ft_strcmp(args[1], "sha256") == 0)
			sha256(ssl, ft_strlen(ssl->line), (uint8_t *)ssl->line);
		ft_strdel(&ssl->line);
		ft_strdel(&line);
	}
	if (ssl->flags.s && ssl->string_index)
		read_string(ssl, argc, args);
	if (ssl->file_index)
	{
		ssl->origin = FILES;
		while (ssl->file_index < argc)
			read_file(ssl, args, ssl->file_index++);
	}
}
