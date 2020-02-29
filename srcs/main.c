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

void	initialize(t_ssl *ssl)
{
	ssl->flags.p = 0;
	ssl->flags.q = 0;
	ssl->flags.r = 0;
	ssl->flags.s = 0;
	ssl->string_index = 0;
	ssl->file_index = 0;
	ssl->file_name = NULL;
	ssl->line = NULL;
	ssl->stdin_args = NULL;
	ssl->words = 0;
	ssl->stdin_buf = NULL;
	ssl->stdin_line = NULL;
}

int			main(int argc, char **argv)
{
	t_ssl	ssl;

	initialize(&ssl);
	if (argc == 1)
		console(&ssl);
	else if (hash_recognized(argv[1]) > 0)
		processing(&ssl, argc, argv);
	else
		error(argv[1]);
	return (0);
}
