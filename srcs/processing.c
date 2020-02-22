/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:06:20 by ysushkov          #+#    #+#             */
/*   Updated: 2019/07/10 17:56:52 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	     flags(t_ssl *ssl, int argc, char **argv)
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

static void	read_file(t_ssl *ssl, char **args, int index)
{
	int		fd;
	char	*line;

	line = NULL;
	ssl->file_name = ft_strdup(args[index]);
	fd = open(ssl->file_name, O_RDONLY);
	if (fd != -1)
	{
		if (get_next_line(fd, &line) == -1)
			read_error(ssl->file_name, args[1]);
		else
		{
			ssl->line = ft_strdup(line);
			if (ft_strcmp(args[1], "md5") == 0)
				md5(ssl, ft_strlen(ssl->line), (uint8_t *)ssl->line);
			else if (ft_strcmp(args[1], "sha256") == 0)
				sha256(ssl, ft_strlen(ssl->line), (uint8_t *)ssl->line);
			if (line != NULL)
				ft_strdel(&line);
			if (ssl->line != NULL)	
				ft_strdel(&ssl->line);
		}
		close(fd);
	}
	else
		no_such_file(ssl->file_name, args[1]);
	ft_strdel(&ssl->file_name);
}

static void read_string(t_ssl *ssl, int argc, char **args)
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
		else if ((i + 1) == argc && ft_strcmp(args[i], "-s") == 0 && !ssl->file_index)
		{
			string_error(args[1]);
		}
	}
}

void	      processing(t_ssl *ssl, int argc, char **args)
{
	char	*line;

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
