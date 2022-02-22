/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 12:38:17 by pmontese          #+#    #+#             */
/*   Updated: 2022/02/22 20:35:44 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

/* used with lst_clear to delete only the t_list elements and not their content */
void	emptyfunc(void *v) { };

/* returns true if c is alpha or underscore */
int		isvalidchar4var(char c, int is_start)
{
	if (is_start && (ft_isalpha(c) || c == '_'))
			return (1);
	if (!is_start && (ft_isalnum(c) || c == '_'))
			return (1);
	return (0);
}

/* appends a character to a string, it allocs space and frees the original string.
str can be null, in that case it returns a string with the character c */
char	*ft_strjoinchar(char *str, char c)
{
	char	*new;
	int		len;
	int		i;

	if (str == NULL)
	{
		new = ft_calloc(2, sizeof(char));
		new[0] = c;
		return (new);
	}
	len = ft_strlen(str);
	new = ft_calloc(len + 2, sizeof(char));
	i = 0;
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	free(str);
	return (new);
}

size_t  ft_wordcount(char const *str, char delimiter)
{
	size_t	i;
	size_t	w;

	i = 0;
	w = 0;
	while (str[i])
	{
		if (str[i] != delimiter)
			w += 1;
		while (str[i] != delimiter && str[i + 1])
			i += 1;
		i += 1;
	}
	return (w);
}

/* returns the t_list at the position pos from lst */
t_list	*ft_lstat(t_list *lst, int pos)
{
	t_list	*tmp;
	int		i;

	tmp = lst;
	i = 0;
	while(tmp && i < pos)
	{
		tmp = tmp->next;
		i++;
	}
	return tmp;
}
