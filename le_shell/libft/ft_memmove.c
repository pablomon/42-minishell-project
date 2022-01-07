/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 21:38:42 by lvintila          #+#    #+#             */
/*   Updated: 2020/01/16 21:42:03 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (src < dst)
		while (n--)
			*(unsigned char *)(dst + n) = *(unsigned char *)(src + n);
	else
		ft_memcpy(dst, src, n);
	return (dst);
}
