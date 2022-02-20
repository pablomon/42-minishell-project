/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 12:16:52 by lvintila          #+#    #+#             */
/*   Updated: 2020/01/22 17:31:53 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (new == NULL)
	{
		new->next = *alst;
		*alst = new;
	}
	else
	{
		new->next = *alst;
		*alst = new;
	}
}
