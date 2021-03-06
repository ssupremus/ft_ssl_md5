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

void		send_line_to_hash(t_ssl *ssl, size_t length, char *hash)
{
	if (ft_strcmp("md5", hash) == 0)
		md5(ssl, length, (uint8_t *)ssl->line);
	else if ((ft_strcmp("sha224", hash) == 0))
		sha224(ssl, length, (uint8_t *)ssl->line);
	else if ((ft_strcmp("sha256", hash) == 0))
		sha256(ssl, length, (uint8_t *)ssl->line);
	else if (ft_strcmp("sha384", hash) == 0)
		sha384(ssl, length, (uint8_t *)ssl->line);
	else if (ft_strcmp("sha512", hash) == 0)
		sha512(ssl, length, (uint8_t *)ssl->line);
}

static void	read_file(t_ssl *ssl, char **args, int index)
{
	size_t	length;
	int		err;

	length = 0;
	ssl->file_name = ft_strdup(args[index]);
	if ((err = file_exists(ssl->file_name)) > 0)
	{
		length = file_length(ssl->file_name);
		ssl->line = reading(ssl->file_name, length);
		send_line_to_hash(ssl, length, args[1]);
		ft_strdel(&ssl->line);
	}
	else if (err == -1 || err == -3)
	{
		if (!(ssl->stdin_args && ft_strcmp(args[index - 1], "-s") == 0))
			no_such_file(ssl->file_name, args[1], err == -1 ? ENOENT : EACCES);
	}
	else if (err == -2)
		read_error(ssl->file_name, args[1]);
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
			send_line_to_hash(ssl, ft_strlen(ssl->line), args[1]);
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
		get_next_line_div(STDIN, &line, 0);
		ssl->line = line != NULL ? ft_strjoin(line, "\n") : ft_strdup("\n");
		send_line_to_hash(ssl, ft_strlen(ssl->line), args[1]);
		ft_strdel(&ssl->line);
		ft_strdel(&line);
	}
	if (ssl->flags.s)
		ssl->string_index ? read_string(ssl, argc, args) :
							string_error(args[1]);
	if (ssl->file_index)
	{
		ssl->origin = FILES;
		while (ssl->file_index < argc)
			read_file(ssl, args, ssl->file_index++);
	}
}
