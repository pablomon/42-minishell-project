/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 12:38:17 by pmontese          #+#    #+#             */
/*   Updated: 2022/01/30 13:59:45 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

char	**make_envp(t_param *param)
{
	char	**envp;
	int		i;
	char	*tmp;

	envp = (char**)(malloc(sizeof(char*) * (param->envc + 1)));
	i = 0;
	while (i < param->envc)
	{
		tmp = ft_strjoin(param->env[i]->key, "=");
		envp[i] = ft_strjoin(tmp, param->env[i]->val);
		free(tmp);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

/* busca si hay una variable con el mismo nombre y cambia su valor
si no lo hay devuelve 0*/
int		try_set_existing_var(t_keyval *var, t_param *param)
{
	int	i;

	i = 0;
	while (i < param->envc)
	{
		if (!ft_strcmp(var->key, param->env[i]->key))
		{
			free(var->key); // usamos el key que ya existe
			free(param->env[i]->val); // usamos el val nuevo
			param->env[i]->val = ft_strdup(var->val);
			return (1);
		}
		i++;
	}
	return (0);
}

/* Damos por hecho que key y value están en el heap*/
void	set_env_var(t_keyval *var, t_param *param)
{
	int			i;
	t_keyval	**new_env;

	if (!try_set_existing_var(var, param)) // si no existe la variable
	{
		// actualiza env
		new_env = (t_keyval**)(malloc(sizeof(t_keyval*) * (param->envc + 1)));
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
	}
}

// esta función presupone que la variable existe
void	unset_env_var(char *name, t_param *param)
{
	t_keyval	**new_env;
	int			i;
	int			j;

	new_env = (t_keyval**)(malloc(sizeof(t_keyval*) * (param->envc - 1)));
	i = 0;
	j = 0;
	while (i < param->envc)
	{
		if (ft_strcmp(name, param->env[i]->key) == 0)
		{
			i++;
			break;
		}
		new_env[j] = param->env[i];
		i++;
		j++;
	}
	if (param->env != NULL)
		free(param->env);
	param->env = new_env;
	param->envc--;
}

char	*mygetenv(char *name, t_param *param)
{
	int i;

	i = 0;
	while (i < param->envc)
	{
		if (ft_strcmp(name, param->env[i]->key) == 0)
			return (param->env[i]->val);
		i++;
	}
	return (NULL);
}

t_keyval	*get_keyval(char *str)
{
	int	len;
	int	len2;
	t_keyval	*pair;

	pair = (t_keyval*)(malloc(sizeof(t_keyval)));
	len = 0;
	while (str[len] != '=')
		len++;
	pair->key = ft_substr(str, 0, len);
	pair->val = ft_strdup(&str[len + 1]);
	return pair;
}