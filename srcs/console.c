/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:06:20 by ysushkov          #+#    #+#             */
/*   Updated: 2020/02/24 19:47:06 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static int	count_words(char *s)
{
	size_t	i;
	size_t	words;
	char	c;

	i = 0;
	c = ' ';
	words = 0;
	while (*(s + i) == c)
		i++;
	while (*(s + i) != '\0')
	{
		if ((*(s + i) != c && *(s + i + 1) == c) ||
			(*(s + i) != c && *(s + i + 1) == '\0'))
			words++;
		i++;
	}
	return (words);
}

void    clean_input(t_ssl *ssl, int argc)
{
    int i;

    i = -1;
    if (ssl->stdin_args != NULL)
    {
        while (++i < argc)
            ft_strdel(&ssl->stdin_args[i]);
        free(ssl->stdin_args);
        ssl->stdin_args = NULL;
    }
    if (ssl->stdin_buf != NULL)
        ft_strdel(&ssl->stdin_buf);
}

static int     hash_recognized(char *hash)
{
    if (ft_strcmp(hash, "md5") == 0 ||
		ft_strcmp(hash, "sha224") == 0 ||
		ft_strcmp(hash, "sha256") == 0 ||
		ft_strcmp(hash, "sha384") == 0 ||
		ft_strcmp(hash, "sha512") == 0)
        return (1);
    return (0);
}

static int		console_options(t_ssl *ssl)
{
	ssl->stdin_buf = ft_strjoin("ft_ssl ", ssl->stdin_line);
	ssl->words = count_words(ssl->stdin_buf);
	ssl->stdin_args = ft_strsplit(ssl->stdin_buf, ' ');
	ft_strdel(&ssl->stdin_buf);
	if (hash_recognized(ssl->stdin_args[1]) > 0)
		processing(ssl, ssl->words, ssl->stdin_args);
	else if (ft_strcmp(ssl->stdin_args[1], "exit") == 0)
	{
		clean_input(ssl, ssl->words);
 		return (-1);
	}
	else
		error(ssl->stdin_args[1]);
	clean_input(ssl, ssl->words);
	return (1);
}

void	console(t_ssl *ssl)
{
	ft_putendl("Type 'exit' to quit");
	while (1)
	{
		ft_putstr("ft_ssl> ");
		if (get_next_line(0, &ssl->stdin_line) > 1)
		{
			ft_strdel(&ssl->stdin_line);
			break ;
		}
		else
		{
			if (console_options(ssl) == -1)
				break ;
		}
		ft_strdel(&ssl->stdin_line);
    }
    if (ssl->stdin_line)
        ft_strdel(&ssl->stdin_line);
}
