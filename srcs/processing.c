#include "../includes/ft_ssl.h"

void	     flags(t_ssl *ssl, int argc, char **argv)
{
	int	i;

	i = 1;
	while (++i < argc)
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
	}
}

static void	read_file(t_ssl *ssl, char **args)
{
	int		fd;
	char	*line;

	ssl->file_name = ft_strdup(args[ssl->file_index]);
	fd = open(ssl->file_name, O_RDONLY);
	if (fd != -1)
	{
			if (get_next_line(fd, &line) == -1)
				read_error(ssl->file_name, "md5");
			else
			{
					ssl->line = ft_strjoin(line, "\n");
					if (ft_strcmp(args[1], "md5") == 0)
						md5(ssl, ft_strlen(ssl->line), (uint8_t *)ssl->line);
					else if (ft_strcmp(args[1], "sha256") == 0)
						sha256(ssl, ft_strlen(ssl->line), (uint8_t *)ssl->line);
					ft_strdel(&ssl->line);
					ft_strdel(&line);
			}
			close(fd);
	}
	else
		no_such_file(ssl->file_name, "md5");
	ft_strdel(&ssl->file_name);
	ssl->file_index++;
}

static void read_string(t_ssl *ssl, char **args)
{
  ssl->origin = STRING;
  ssl->line = ft_strdup(args[ssl->string_index]);
  if (ft_strcmp(args[1], "md5") == 0)
    md5(ssl, ft_strlen(ssl->line), (uint8_t *)ssl->line);
  else if (ft_strcmp(args[1], "sha256") == 0)
    sha256(ssl, ft_strlen(ssl->line), (uint8_t *)ssl->line);
  ft_strdel(&ssl->line);
}

void	      processing(t_ssl *ssl, int argc, char **args)
{
	char	*line;

	flags(ssl, argc, args);
	if (ssl->flags.p || (!ssl->flags.s && !ssl->file_index))
	{
		ssl->origin = STDIN;
		get_next_line(STDIN, &line);
		ssl->line = ft_strjoin(line, "\n");
		if (ft_strcmp(args[1], "md5") == 0)
			md5(ssl, ft_strlen(ssl->line), (uint8_t *)ssl->line);
		else if (ft_strcmp(args[1], "sha256") == 0)
			sha256(ssl, ft_strlen(ssl->line), (uint8_t *)ssl->line);
		ft_strdel(&ssl->line);
		ft_strdel(&line);
	}
	if (ssl->flags.s && ssl->string_index)
    read_string(ssl, args);
	if (ssl->file_index)
	{
		ssl->origin = FILES;
		while (ssl->file_index < argc)
			read_file(ssl, args);
	}
}
