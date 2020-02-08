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

void	flags(t_ssl *ssl, int length, char **args)
{
	int	i;

	i = 2;
	while (i < length && args[i][0] == '-' && ft_strlen(args[i]) == 2)
	{
		if (args[i][1] == 'p')
			ssl->flags.p = 1;
		else if (args[i][1] == 'q')
			ssl->flags.q = 1;
		else if (args[i][1] == 'r')
			ssl->flags.r = 1;
		else if (args[i][1] == 's')
			ssl->flags.s = 1;
		else
		{
			ft_putendl("WRONG FLAG");
			exit(-1);
		}
		i++;
	}
}

void	processing(t_ssl *ssl, int length, char **args)
{
	flags(ssl, length, args);
	if (ft_strcmp(args[1], "md5"))
		md5(ssl, length, args);
}

void	initialize(t_ssl *ssl)
{
	ssl->flags.p = 0;
	ssl->flags.q = 0;
	ssl->flags.r = 0;
	ssl->flags.s = 0;
}

int	main(int argc, char **argv)
{
	t_ssl	ssl;

	initialize(&ssl);
	if (argc == 1)
		usage();
	else if (ft_strcmp(argv[1], "md5") == 0 || ft_strcmp(argv[1], "sha256") == 0)
		processing(&ssl, argc, argv);
	else
		error(argv[1]);
	return (0);
}
