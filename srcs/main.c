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

static void	initialize(t_ssl *ssl)
{
	ssl->flags.p = 0;
	ssl->flags.q = 0;
	ssl->flags.r = 0;
	ssl->flags.s = 0;
	ssl->string_index = 0;
	ssl->file_index = 0;
	ssl->file_name = NULL;
	ssl->line = NULL;
}

int			main(int argc, char **argv)
{
	t_ssl	ssl;

	initialize(&ssl);
	flags(&ssl, argc, argv);
	if (argc == 1)
		usage();
	else if (ft_strcmp(argv[1], "md5") == 0 ||
			ft_strcmp(argv[1], "sha256") == 0 ||
			ft_strcmp(argv[1], "sha512") == 0)
		processing(&ssl, argc, argv);
	else
		error(argv[1]);
	return (0);
}
