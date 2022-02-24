/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:54:19 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/24 13:01:54 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

void	bi_env(t_param *param, int is_child)
{
	int	i;

	if (!is_child)
		return ;
	i = 0;
	while (i < param->envc)
	{
		if (param->env[i]->val)
			printf("%s=%s\n", param->env[i]->key, param->env[i]->val);
		i++;
	}
}

char	*cd_getarg(t_command *cmd, t_param *param)
{
	char	*arg;

	if (cmd->argc == 1)
	{
		arg = mygetenv("HOME", param);
		if (!arg)
		{
			my_perror(NOHOME, "", 1);
			return (NULL);
		}
	}
	else
		arg = cmd->argv[1];
	return (arg);
}

int	bi_cd(t_command *cmd, t_param *param, int ischild)
{
	char		*pwd;
	char		*arg;
	DIR			*dir;

	if (ischild || param->cmdc > 1)
		return (0);
	arg = cd_getarg(cmd, param);
	if (access(arg, F_OK) == -1)
		return (my_perror(NOFILDIR, arg, 1));
	dir = opendir(arg);
	if (!dir)
	{
		closedir(dir);
		return (my_perror(NOT_DIR, arg, 1));
	}
	pwd = getcwd(NULL, 0);
	my_setenv("OLDPWD", pwd, param);
	chdir(arg);
	free(pwd);
	pwd = getcwd(NULL, 0);
	my_setenv("PWD", pwd, param);
	closedir(dir);
	free(pwd);
	update_prompt(param);
	return (0);
}