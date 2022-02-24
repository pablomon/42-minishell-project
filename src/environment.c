/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 12:38:17 by pmontese          #+#    #+#             */
/*   Updated: 2022/02/24 00:06:37 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

/* busca si hay una variable con el mismo nombre y cambia su valor,
si no lo hay devuelve 0 */

int	try_set_existing_var(t_keyval *var, t_param *param)
{
	int	i;

	i = 0;
	while (i < param->envc)
	{
		if (ft_strcmp(var->key, param->env[i]->key) == 0)
		{
			free(param->env[i]->key);
			free(param->env[i]->val);
			free(param->env[i]);
			param->env[i] = var;
			return (1);
		}
		i++;
	}
	return (0);
}

void	set_env_var(t_keyval *var, t_param *param)
{
	int			i;
	t_keyval	**new_env;

	if (!try_set_existing_var(var, param))
	{
		new_env = (t_keyval **)(malloc(sizeof(t_keyval *) * (param->envc + 1)));
		i = 0;
		while (i < param->envc)
		{
			new_env[i] = param->env[i];
			i++;
		}
		new_env[i] = var;
		if (param->env != NULL)
			free(param->env);
		param->env = new_env;
		param->envc++;
		if (var->val)
			param->envvalc++;
	}
}

char	*clean_val(char *str)
{
	int		i;
	char	*new;
	int		can_space;

	i = 0;
	new = ft_strdup("");
	can_space = 1;
	while (str[i])
	{
		if (ft_isspace(str[i]))
		{
			if (can_space)
			{
				new = ft_strjoinchar(new, str[i]);
				can_space = 0;
			}
		}
		else
		{
			can_space = 1;
			new = ft_strjoinchar(new, str[i]);
		}
		i++;
	}
	return (new);
}

/* Allocate memory for a new t_keyval. A str without '=' is allowd (value = 0)
limpia de espacios la parte a la derecha del igual*/

t_keyval	*get_keyval(char *str)
{
	int			len;
	int			len2;
	t_keyval	*pair;

	pair = (t_keyval *)(malloc(sizeof(t_keyval)));
	pair->val = NULL;
	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	pair->key = ft_substr(str, 0, len);
	if (len != ft_strlen(str))
		pair->val = clean_val(&str[len + 1]);
	return (pair);
}

void	my_setenv(char *name, char *value, t_param *param)
{
	t_keyval	*pair;

	pair = (t_keyval *)(malloc(sizeof(t_keyval)));
	pair->key = ft_strdup(name);
	pair->val = ft_strdup(value);
	set_env_var(pair, param);
}
