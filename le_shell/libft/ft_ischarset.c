/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ischarset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <lvintila@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 20:28:30 by lvintila          #+#    #+#             */
/*   Updated: 2021/04/20 21:14:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_ischarset(int c, const char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}
