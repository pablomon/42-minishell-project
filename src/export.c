/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 12:38:17 by pmontese          #+#    #+#             */
/*   Updated: 2022/02/23 18:50:43 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

/* Returns 1 if "s1 > s2" */
int	comparator(t_keyval *kv1, t_keyval *kv2)
{
	char	*s1;
	char	*s2;
	int		i;

	s1 = kv1->key;
	s2 = kv2->key;
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] > s2[i])
			return (1);
		if (s1[i] < s2[i])
			return (0);
		i++;
	}
	if (s1[i])
		return (1);
	if (s2[i])
		return (0);
	return (0);
}

void	order_export(t_list *first, t_param *param)
{
	int			i;
	t_list		*list;
	t_list		*tmp;
	t_list		*tmp2;

	i = 0;
	while (i < param->envc)
	{
		list = first;
		while (list->next)
		{
			if (comparator((t_keyval *)(list->next->content), param->env[i]))
				break ;
			list = list->next;
		}
		if (list->next)
		{
			tmp2 = ft_lstnew(param->env[i]);
			tmp2->next = list->next;
			list->next = tmp2;
		}
		else
			ft_lstadd_back(&first, ft_lstnew(param->env[i]));
		i++;
	}
}

void	print_export(t_param *param)
{
	int			i;
	t_list		*first;
	t_list		*lst;
	t_keyval	*kv;

	first = ft_lstnew(param);
	order_export(first, param);
	lst = first->next;
	i = 0;
	while (i < param->envc)
	{
		printf("declare -x ");
		kv = (t_keyval *)(lst->content);
		printf("%s", kv->key);
		if (kv->val)
			printf("=\"%s\"", kv->val);
		printf("\n");
		lst = lst->next;
		i++;
	}
	ft_lstclear(&first, &emptyfunc);
}
