/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 10:19:04 by lvintila          #+#    #+#             */
/*   Updated: 2021/04/21 18:53:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	dst = malloc(sizeof(char) * (len + 1));
	if (!(dst))
		return (NULL);
	while (i < len && s[i] != '\0')
	{
		dst[i] = s[start];
		start++;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
