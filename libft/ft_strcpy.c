/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 20:09:36 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/24 00:28:16 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, char *src)
{
	int		i;
	char	a;

	i = 0;
	while (src[i] != '\0')
	{
		a = src[i];
		dest[i] = a;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
