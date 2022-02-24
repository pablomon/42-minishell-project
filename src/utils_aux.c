/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <lvintila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 21:11:43 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/23 23:15:55 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

int	ft_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

char	**ft_dup_arr(char **arr)
{
	char	**out;
	int		n_rows;
	int		i;

	i = 0;
	n_rows = ft_arr_len(arr);
	out = malloc(sizeof(char *) * (n_rows + 1));
	if (!out)
		return (NULL);
	while (arr[i])
	{
		out[i] = ft_strdup(arr[i]);
		if (!out[i])
		{
			ft_free_arr(&out);
			return (NULL);
		}
		i++;
	}
	out[i] = NULL;
	return (out);
}

char	**ft_arr_replace_in(char ***big, char **small, int n)
{
	char	**aux;
	int		num[3];

	num[0] = -1;
	num[1] = -1;
	num[2] = -1;
	if (!big || !*big || n < 0 || n >= ft_arr_len(*big))
		return (NULL);
	aux = ft_calloc(ft_arr_len(*big) + ft_arr_len(small), sizeof(char *));
	while (aux && big[0][++num[0]])
	{
		if (num[0] != n)
			aux[++num[2]] = ft_strdup(big[0][num[0]]);
		else
		{
			while (small && small[++num[1]])
				aux[++num[2]] = ft_strdup(small[num[1]]);
		}
	}
	ft_free_arr(big);
	*big = aux;
	return (*big);
}

void	ft_free_arr(char ***arr)
{
	int	i;

	i = 0;
	while (arr && arr[0] && arr[0][i])
	{
		free(arr[0][i]);
		i++;
	}
	if (arr)
	{
		free(arr[0]);
		*arr = NULL;
	}
}

int	ft_put_arr_fd(char **arr, int fd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (arr && arr[i])
	{
		count += ft_putendl_fd(arr[i], fd);
		i++;
	}
	return (count);
}
