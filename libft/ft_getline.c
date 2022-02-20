/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:51:05 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/10 20:51:43 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_getline(char **str, char **line, char *s)
{
	int		ret;
	char	*tmp;

	ret = 0;
	if (*s == '\n')
		ret = 1;
	*s = 0;
	*line = ft_strjoin("", *str);
	if (ret == 0 && ft_strlen(*str))
	{
		*str = ft_strnew(1);
		return (1);
	}
	else if (ret == 0 && !(ft_strlen(*str)))
		return (0);
	tmp = *str;
	*str = ft_strjoin(s + 1, "");
	free(tmp);
	return (ret);
}
