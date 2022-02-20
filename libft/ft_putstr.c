/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <lvintila@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 10:05:37 by lvintila          #+#    #+#             */
/*   Updated: 2021/07/05 21:48:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char const *s)
{
	size_t	len;

	if (s == NULL)
		return ;
	len = ft_strlen(s);
	if (len > 0)
	{
		write(1, s, len);
	}
}
