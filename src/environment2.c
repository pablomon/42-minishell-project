/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 00:02:49 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/24 15:52:07 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

char	*clean_val(char *str)
{
	int		i;
	int		lft;
	int		rgt;
	char	*new;
	int		can_space;

	can_space = 1;
	new = ft_strdup("");
	i = -1;
	while (str[++i])
	{
		if (ft_isspace(str[i]))
		{
			if (can_space)
				can_space = 0;
		}
		else
			can_space = 1;
		new = ft_strjoinchar(new, str[i]);
	}
	return (new);
}

t_keyval	*get_keyval(char *str)
{
	int			len;
	int			len2;
	t_keyval	*pair;

	pair = (t_keyval *)(malloc(sizeof(t_keyval)));
	pair->val = NULL;
	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	pair->key = ft_substr(str, 0, len);
	if (len != ft_strlen(str))
		pair->val = clean_val(&str[len + 1]);
	return (pair);
}
