/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 19:14:46 by lvintila          #+#    #+#             */
/*   Updated: 2021/04/21 19:46:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	index_count;

	index_count = 0;
	if (!s1)
		return (NULL);
	join = (char *)malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!join)
		return (NULL);
	while (*s1 != '\0')
	{
		*join = *s1;
		join++;
		s1++;
		index_count++;
	}
	while (*s2 != 0)
	{
		*join = *s2;
		join++;
		s2++;
		index_count++;
	}
	*join = '\0';
	return (join - index_count);
}

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

char	*ft_strdup(const char *s1)
{
	char	*new;
	size_t	i;

	new = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!(new))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_strtab(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
