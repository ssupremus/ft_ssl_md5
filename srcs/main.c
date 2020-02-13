#include "../includes/ft_ssl.h"
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

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

void	flags(t_ssl *ssl, int argc, char **argv)
{
	int	i;

	i = 2;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-p") == 0)
			ssl->flags.p = 1;
		else if (ft_strcmp(argv[i], "-q") == 0)
			ssl->flags.q = 1;
		else if (ft_strcmp(argv[i], "-r") == 0)
			ssl->flags.r = 1;
		else if (ft_strcmp(argv[i], "-s") == 0)
		{
			ssl->flags.s = 1;
			if (i < (argc - 1))
				ssl->string_index = i + 1;
			i++;
		}
		else
		{
			ssl->file_index = i;
			break ;
		}
		i++;
	}
}

void	processing(t_ssl *ssl, int argc, char **args)
{
	char	*line;
	int		fd;

	flags(ssl, argc, args);
	if (ssl->flags.p || (!ssl->flags.s && !ssl->file_index))
	{
		ssl->origin = STDIN;
		get_next_line(STDIN, &line);
		ssl->line = ft_strjoin(line, "\n");
		if (ft_strcmp(args[1], "md5") == 0)
			md5(ssl, ft_strlen(ssl->line), (uint8_t *)ssl->line);
		ft_strdel(&ssl->line);
		ft_strdel(&line);
	}
	if (ssl->flags.s && ssl->string_index)
	{
		ssl->origin = STRING;
		ssl->line = ft_strdup(args[ssl->string_index]);
		md5(ssl, ft_strlen(ssl->line), (uint8_t *)ssl->line);
		ft_strdel(&ssl->line);
	}
	if (ssl->file_index)
	{
		while (ssl->file_index < argc)
		{
			ssl->file_name = ft_strdup(args[ssl->file_index]);
			fd = open(ssl->file_name, O_RDONLY);
			if (fd != -1)
			{
					ssl->origin = FILES;
					if (get_next_line(fd, &line) == -1)
						read_error(ssl->file_name);
					else
					{
							ssl->line = ft_strjoin(line, "\n");
							md5(ssl, ft_strlen(ssl->line), (uint8_t *)ssl->line);
							ft_strdel(&ssl->line);
							ft_strdel(&line);
					}
					close(fd);
			}
			else
				no_such_file(ssl->file_name);
			ft_strdel(&ssl->file_name);
			ssl->file_index++;
		}
	}
}

void	initialize(t_ssl *ssl)
{
	ssl->flags.p = 0;
	ssl->flags.q = 0;
	ssl->flags.r = 0;
	ssl->flags.s = 0;
	ssl->string_index = 0;
	ssl->file_index = 0;
	ssl->file_name = NULL;
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
