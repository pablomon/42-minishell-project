/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <lvintila@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 12:48:11 by lvintila          #+#    #+#             */
/*   Updated: 2021/12/26 22:23:21 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
char	*ft_strtok(char *s1, const char *delim)
{
	static char *str = NULL;

	if (s1)
		str = s1;
	if (!str)
		return (NULL);
	while (*str && ft_strchr(delim, *str))
		str++;
	while (str && !ft_strchr(delim, *str))
		str++;
	if (!*str)
		return (NULL);
	return (str);
}

*/

/*
char	*ft_strtok(char *s1, const char *delim)
{
	uint8_t	hash[256];
	int		i;

	if (!s1)
		return (NULL);
	if (!delim)
		return (ft_strdup(s1));
	ft_bzero(&hash, 256);
	i = -1;
	while (delim[++i])
		hash[(int)delim[i]] = 1;
	i = -1;
	while (s1[++i])
	{
		if (hash[(int)s1[i]])
			return (ft_strndup(s1, i));
	}
	return (ft_strdup(s1));
}
*/

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT.  */
size_t	ft_strspn(const char *s, const char *accept)
{
	const char *ptr;
	const char *aux;
	size_t count = 0;

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
			return count;
		else
			++count;
		++ptr;
	}
	return count;
}


/* Return the length of the maximum initial segment of S
   which contains no characters from REJECT.  */
size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t count;

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

/* Parse S into tokens separated by characters in DELIM.
   If S is NULL, the saved pointer in SAVE_PTR is used as
   the next starting point.  For example:
	char s[] = "-abc-=-def";
	char *sp;
	x = strtok_r(s, "-", &sp);	// x = "abc", sp = "=-def"
	x = strtok_r(NULL, "-=", &sp);	// x = "def", sp = NULL
	x = strtok_r(NULL, "=", &sp);	// x = NULL
		// s = "abc\0-def\0"
*/
char *ft_strtok_r(char *s, const char *delim, char **save_ptr)
{
	char *end;

	if (s == NULL)
		s = *save_ptr;

	if (*s == '\0')
    {
      *save_ptr = s;
      return NULL;
    }

	/* Scan leading delimiters.  */
	s += ft_strspn(s, delim);
	if (*s == '\0')
    {
		*save_ptr = s;
		return (NULL);
    }

	/* Find the end of the token.  */
	end = s + ft_strcspn(s, delim);
	if (*end == '\0')
	{
		*save_ptr = end;
		return (s);
    }

	/* Terminate the token and make *SAVE_PTR point past it.  */
	*end = '\0';
	*save_ptr = end + 1;
	return (s);
}

/* Parse S into tokens separated by characters in DELIM.
   If S is NULL, the last string strtok() was called with is
   used.  For example:
	char s[] = "-abc-=-def";
	x = strtok(s, "-");		// x = "abc"
	x = strtok(NULL, "-=");		// x = "def"
	x = strtok(NULL, "=");		// x = NULL
		// s = "abc\0=-def\0"
*/
char *ft_strtok(char *s, const char *delim)
{
  static char *olds;
  return ft_strtok_r(s, delim, &olds);
}
