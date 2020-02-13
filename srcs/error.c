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
	exit(-1);
}
