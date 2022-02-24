/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 00:02:49 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/24 00:06:25 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

char	**make_envp(t_param *param)
{
	char	**envp;
	int		i;
	int		h;
	char	*tmp;

	envp = (char **)(malloc(sizeof(char *) * (param->envvalc + 1)));
	i = 0;
	h = 0;
	while (i < param->envc)
	{
		if (!param->env[i]->val)
		{
			i++;
			continue ;
		}
		tmp = ft_strjoin(param->env[i]->key, "=");
		envp[h] = ft_strjoin(tmp, param->env[i]->val);
		free(tmp);
		i++;
		h++;
	}
	envp[h] = NULL;
	return (envp);
}

char	*mygetenv(char *name, t_param *param)
{
	int	i;

	if (name == NULL)
		return (NULL);
	i = 0;
	while (i < param->envc)
	{
		if (ft_strcmp(name, param->env[i]->key) == 0)
			return (param->env[i]->val);
		i++;
	}
	return (NULL);
}

void	free_param_env(t_param *param)
{
	t_keyval	**new_env;
	int			i;
	int			j;

	free(param->env[i]->key);
	if (param->env[i]->val)
		param->envvalc--;
	free(param->env[i]->val);
	free(param->env[i]);
}

void	unset_env_var(char *name, t_param *param)
{
	t_keyval	**new_env;
	int			i;
	int			j;

	new_env = (t_keyval **)(malloc(sizeof(t_keyval *) * (param->envc - 1)));
	i = 0;
	j = 0;
	while (i < param->envc)
	{
		if (ft_strcmp(name, param->env[i]->key) == 0)
		{
			free_param_env(param);
			i++;
			continue ;
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
