/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:49:56 by lvintila          #+#    #+#             */
/*   Updated: 2021/12/21 18:50:05 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *res;

	res = malloc(size + 1);
	if (!res)
		return (NULL);
	ft_bzero(res, size + 1);
	return (res);
}
