#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft/libft.h"

typedef struct    s_flag
{
  int             p;
  int             q;
  int             r;
  int             s;
}                 t_flag;

typedef struct    s_ssl
{
  t_flag          flags;
}                 t_ssl;

#endif
