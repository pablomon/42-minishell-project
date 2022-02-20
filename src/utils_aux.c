/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <lvintila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 21:11:43 by lvintila          #+#    #+#             */
/*   Updated: 2022/01/27 22:34:28 by lvintila         ###   ########.fr       */
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

int	ft_strchr_i(const char *s, int c)
{
	unsigned char	c_unsigned;
	int				i;

	i = 0;
	if (!s)
		return (-1);
	c_unsigned = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == c_unsigned)
			return (i);
		i++;
	}
	if (c_unsigned == '\0')
		return (i);
	return (-1);
}

char	**ft_extend_arr(char **in, char *new_str)
{
	char	**out;
	int		len;
	int		i;

	i = -1;
	out = NULL;
	if (!new_str)
		return (in);
	len = ft_arr_len(in);
	out = malloc(sizeof(char *) * (len + 2));
	out[len + 1] = NULL;
	if (!out)
		return (in);
	while (++i < len)
	{
        printf("out[0] es: %s\n", out[0]);
		out[i] = ft_strdup(in[i]);
        printf("check strdup ---- > \n");
	 	if (!out[i])
		{
			ft_free_arr(&in);
			ft_free_arr(&out);
		}
	}
	out[i] = ft_strdup(new_str);
	ft_free_arr(&in);
	return (out);
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