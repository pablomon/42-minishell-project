/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 00:02:49 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/25 01:04:26 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

char	**make_envp(t_param *param)
{
	char	**envp;
	int		i;
	int		h;
	char	*tmp;

	envp = (char **)(malloc(sizeof(char *) * (param->envvalc + 1)));
	i = 0;
	h = 0;
	while (i < param->envc)
	{
		if (!param->env[i]->val)
		{
			i++;
			continue ;
		}
		tmp = ft_strjoin(param->env[i]->key, "=");
		envp[h] = ft_strjoin(tmp, param->env[i]->val);
		free(tmp);
		i++;
		h++;
	}
	envp[h] = NULL;
	return (envp);
}

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
