/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:06:20 by ysushkov          #+#    #+#             */
/*   Updated: 2020/02/24 20:07:17 by ysushkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft/libft.h"
# include <stdint.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>

# define STDIN 0
# define STRING 1
# define FILES 2
# define MD5 5
# define SHA256 256
# define R(n) ((n >> 24)|((n & 0xff0000) >> 8)|((n & 0xff00) << 8)|(n << 24))
# define LEFT(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
# define RIGHT(x, y) ((x >> y) | (x << (32 - y)))

typedef struct		s_flag
{
	int		p;
	int		q;
	int		r;
	int		s;
}					t_flag;

typedef struct		s_ssl
{
	char			*line;
	t_flag			flags;
	int				string_index;
	int				file_index;
	char			*file_name;
	uint32_t		a0;
	uint32_t		b0;
	uint32_t		c0;
	uint32_t		d0;
	uint32_t		e0;
	uint32_t		f0;
	uint32_t		g0;
	uint32_t		h0;
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h;
	uint32_t		*m;
	uint32_t		tmp;
	uint32_t		tmp2;
	uint32_t		*msg_32;
	size_t			len_bit;
	int				chunk;
	unsigned char	*padded_message;
	int				origin;
}					t_ssl;

void				usage(void);
void				error(char *arg);
void				no_such_file(char *file_name, char *hash, int e);
void				string_error(char *hash);
void				read_error(char *file_name, char *hash);
void				processing(t_ssl *ssl, int argc, char **args);
void				flags(t_ssl *ssl, int argc, char **argv);
uint32_t			reverse_number(uint32_t n);
int					md5(t_ssl *ssl, size_t length, uint8_t *line);
void				print_md5(t_ssl *ssl);
void				print_sha256(t_ssl *ssl);
int					sha256(t_ssl *ssl, size_t length, uint8_t *line);
char				*reading(char *name, size_t length);
size_t				file_length(char *name);
int					file_exists(char *name);

#endif
