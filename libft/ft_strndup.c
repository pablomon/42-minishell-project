/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 20:42:23 by lvintila          #+#    #+#             */
/*   Updated: 2021/12/26 20:44:29 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t len)
{
	char	*str;

	if (!(str = (char*)malloc(len + 1)))
		return (NULL);
	return (ft_strncpy(str, src, len));
}
