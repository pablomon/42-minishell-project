/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 19:50:30 by lvintila          #+#    #+#             */
/*   Updated: 2021/04/21 18:53:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_pos;

	last_pos = 0;
	while (*s)
	{
		if (*s == c)
			last_pos = (char *)s;
		s++;
	}
	if (last_pos)
		return (last_pos);
	if (c == '\0')
		return ((char *)s);
	return (0);
}
