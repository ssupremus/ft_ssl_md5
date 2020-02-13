#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft/libft.h"
# include <stdint.h>

# define STDIN 0
# define STRING 1
# define FILES 2

typedef struct    s_flag
{
  int             p;
  int             q;
  int             r;
  int             s;
}                 t_flag;

typedef struct    s_ssl
{
  char            *line;
  t_flag          flags;
  int             string_index;
  int             file_index;
  char            *file_name;
  uint32_t        a0;
  uint32_t        b0;
  uint32_t        c0;
  uint32_t        d0;
  uint32_t        a;
  uint32_t        b;
  uint32_t        c;
  uint32_t        d;
  uint32_t        e;
  uint32_t        f;
  uint32_t        g;
  uint32_t        *w;
  uint32_t        tmp;
  size_t          len;
  int             chunk;
  unsigned char   *padded_message;
  int             origin;
}                 t_ssl;

int		md5(t_ssl *ssl, size_t length, uint8_t *line);
void  print_md5(t_ssl *ssl);
void  no_such_file(char *file_name);
void  read_error(char *file_name);

#endif
