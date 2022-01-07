/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:51:05 by lvintila          #+#    #+#             */
/*   Updated: 2021/12/21 18:51:27 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getline(char **str, char **line, char *s)
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
