#include "../includes/ft_ssl.h"

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

void	processing(int length, char **args)
{
	int i;

	i = 1;
	while (i < length)
		ft_putendl(args[i++]);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		usage();
	else if (ft_strcmp(argv[1], "md5") == 0 || ft_strcmp(argv[1], "sha256") == 0)
		processing(argc, argv);
	else
		error(argv[1]);
	return (0);
}
