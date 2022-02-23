/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:46:25 by pmontese          #+#    #+#             */
/*   Updated: 2022/02/23 18:47:56 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

#define DEBUG 0

/* returns the first expansion possible
or $ if not expansion possible */
char	*expand2(char *str, int *read, t_param *param)
{
	char	*var_name;
	char	*ret;

	if (str[0] == '?')
	{
		*read = *read + 1;
		return (ft_itoa(g_status));
	}
	if (!isvalidchar4var(str[0], 1))
	{
		return (ft_strdup("$"));
	}
	var_name = NULL;
	while (str[*read] && isvalidchar4var(str[*read], 0))
	{
		var_name = ft_strjoinchar(var_name, str[*read]);
		*read = *read + 1;
	}
	ret = mygetenv(var_name, param);
	if (ret == NULL)
		ret = ft_strdup("");
	else
		ret = ft_strdup(mygetenv(var_name, param));
	free (var_name);
	return (ret);
}

char	*the_expanse(char *str, t_param *param)
{
	char	*expanded;
	int		i;
	int		h;
	char	*tmp;
	char	*res;

	expanded = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			h = 0;
			res = expand2(&str[i + 1], &h, param);
			i += h + 1;
			tmp = expanded;
			expanded = ft_strjoin(expanded, res);
			free(res);
			free(tmp);
			continue ;
		}
		expanded = ft_strjoinchar(expanded, str[i]);
		i++;
	}
	return (expanded);
}

void	expand_tokens(t_list *tkn_lst, t_param *param)
{
	int		i;
	t_list	*tmp;
	t_token	*t;
	char	*expanded;

	i = 0;
	tmp = tkn_lst;
	while (tmp)
	{
		t = (t_token *)(tmp->content);
		if (t->expandable)
		{
			expanded = the_expanse(t->cnt, param);
			free(t->cnt);
			((t_token *)(tmp->content))->cnt = expanded;
		}
		tmp = tmp->next;
	}
}
