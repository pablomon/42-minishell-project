/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:59:52 by pmontese          #+#    #+#             */
/*   Updated: 2022/02/23 19:01:03 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

void	init_param2(t_param *param, char **env, char *cwd)
{
	int			i;
	t_keyval	*keyval;

	i = 0;
	while (env[i] != NULL)
	{
		keyval = get_keyval(env[i]);
		set_env_var(keyval, param);
		i++ ;
	}
	if (!mygetenv("PATH", param))
		my_setenv("PATH", cwd, param);
	free (cwd);
}

void	init_param(t_param *param, char **env, char *cwd)
{
	int			i;
	char		*str;

	param->line = NULL;
	param->default_in = 0;
	param->default_out = 0;
	param->fd_in = 0;
	param->fd_out = 0;
	param->cmdc = 0;
	param->envc = 0;
	param->envvalc = 0;
	param->env = NULL;
	param->syntx_err = 0;
	param->tkn_lst = NULL;
	param->cmd_lst = NULL;
	param->prompt = NULL;
	init_param2(param, env, cwd);
}
