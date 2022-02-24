/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <lvintila@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 12:48:11 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/24 00:37:03 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s, const char *accept)
{
	const char	*ptr;
	const char	*aux;
	size_t		count;

	count = 0;
	ptr = s;
	while (*ptr != '\0')
	{
		aux = accept;
		while (*aux != '\0')
		{
			if (*ptr == *aux)
				break ;
			++aux;
		}
		if (*aux == '\0')
			return (count);
		else
			++count;
		++ptr;
	}
	return (count);
}

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		if (ft_strchr(reject, *s++) == NULL)
			++count;
		else
			return (count);
	}
	return (count);
}

char	*ft_strtok_r(char *s, const char *delim, char **save_ptr)
{
	char	*end;

	if (s == NULL)
		s = *save_ptr;
	if (*s == '\0')
	{
		*save_ptr = s;
		return (NULL);
	}
	s += ft_strspn(s, delim);
	if (*s == '\0')
	{
		*save_ptr = s;
		return (NULL);
	}
	end = s + ft_strcspn(s, delim);
	if (*end == '\0')
	{
		*save_ptr = end;
		return (s);
	}
	*end = '\0';
	*save_ptr = end + 1;
	return (s);
}

char	*ft_strtok(char *s, const char *delim)
{
	static char	*olds;

	return (ft_strtok_r(s, delim, &olds));
}
