/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_div.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 12:06:20 by ysushkov          #+#    #+#             */
/*   Updated: 2018/07/10 17:56:52 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 2048
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"

int		get_next_line(const int fd, char **line);
int		get_next_line_div(const int fd, char **line, char div);

#endif
