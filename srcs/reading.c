#include "../includes/ft_ssl.h"

static int		find_breakpoint(char *buf, int ret)
{
	int i;

	i = 0;
	while (buf[i])
		i++;
	if (i < ret)
		return (-1);
	return (1);
}

int             reading(int fd, char **line)
{
	char	*str;
	int		ret;
	char	buf[8000000 + 1];
	char	*temp;

	temp = NULL;
	if (fd < 0 || fd > 4864)
		return (-1);
	str = malloc(1);
	str[0] = 0;
	while ((ret = read(fd, buf, 8000000)) > 0)
	{
		buf[ret] = 0;
		temp = ft_strjoin(str, buf);
		ft_strdel(&str);
		str = ft_strdup(temp);
		ft_strdel(&temp);
		if (!find_breakpoint(buf, ret))
			break ;
	}
	if (ret < 0)
		return (-1);
	*line = ft_strdup(str);
	ft_strdel(&str);
	return (1);
}