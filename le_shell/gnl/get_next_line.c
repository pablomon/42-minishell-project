/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 19:13:32 by lvintila          #+#    #+#             */
/*   Updated: 2021/04/21 20:05:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_file(int fd, char *buf, char **str)
{
	int		ret;
	char	*temp;

	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		temp = ft_strdup(*str);
		free(*str);
		*str = NULL;
		*str = ft_strjoin(temp, buf);
		free(temp);
		temp = NULL;
		if (ft_strtab(*str) != -1)
			break ;
	}
	free(buf);
	buf = NULL;
	return (ret);
}

int	check_line(char **line, char **str, int ret)
{
	char	*tmp;

	if (ret == 0)
	{
		*line = ft_strdup(*str);
		free(*str);
		*str = NULL;
		return (0);
	}
	*line = ft_substr(*str, 0, ft_strtab(*str));
	tmp = *str;
	*str = ft_substr(tmp, ft_strtab(tmp) + 1, ft_strlen(tmp) - ft_strtab(tmp));
	free(tmp);
	tmp = NULL;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*str[4096];
	char		*buf;
	int			ret;

	buf = NULL;
	ret = 1;
	buf = malloc(BUFFER_SIZE + 1);
	if (fd == -1 || line == NULL || buf == NULL
		|| BUFFER_SIZE == 0 || read(fd, buf, 0) == -1)
	{
		free(buf);
		buf = NULL;
		return (-1);
	}
	if (str[fd] == NULL)
		str[fd] = ft_strdup("");
	if (ft_strtab(str[fd]) == -1)
		ret = read_file(fd, buf, &str[fd]);
	else
	{
		free(buf);
		buf = NULL;
	}
	return (check_line(line, &str[fd], ret));
}
