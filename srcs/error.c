/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:06:20 by ysushkov          #+#    #+#             */
/*   Updated: 2019/07/10 17:56:52 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	no_such_file(char *file_name, char *hash)
{
	ft_putstr("ft_ssl: ");
	ft_putstr(hash);
	ft_putstr(": ");
	ft_putstr(file_name);
	ft_putendl(": No such file or directory");
}

void	string_error(char *hash)
{
	ft_putstr("ft_ssl: ");
	ft_putstr(hash);
	ft_putendl(": -s flag should be followed by a string");
}

void	read_error(char *file_name, char *hash)
{
	ft_putstr("ft_ssl: ");
	ft_putstr(hash);
	ft_putstr(": read error in ");
	ft_putendl(file_name);
}

void	usage(void)
{
	ft_putendl("usage: ft_ssl command [command opts] [command args]");
	exit(-1);
}

void	error(char *arg)
{
	ft_putstr("ft_ssl: Error: '");
	ft_putstr(arg);
	ft_putendl("' is an invalid command.");
	ft_putendl("\nStandard commands:");
	ft_putendl("\nMessage Digest commands:");
	ft_putendl("md5");
	ft_putendl("sha256");
	ft_putendl("\nCipher commands:");
	ft_putendl("-p, echo STDIN to STDOUT and append the checksum to STDOUT");
	ft_putendl("-q, quiet mode");
	ft_putendl("-r, reverse the format of the output.");
	ft_putendl("-s, print the sum of the given string");
	exit(-1);
}
