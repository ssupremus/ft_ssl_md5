#include "../includes/ft_ssl.h"

void no_such_file(char *file_name, char *hash)
{
  ft_putstr("ft_ssl: ");
  ft_putstr(hash);
  ft_putstr(": ");
  ft_putstr(file_name);
  ft_putendl(": No such file or directory");
}

void read_error(char *file_name, char *hash)
{
  ft_putstr("ft_ssl: ");
  ft_putstr(hash);
  ft_putstr(": read error in ");
  ft_putendl(file_name);
}
