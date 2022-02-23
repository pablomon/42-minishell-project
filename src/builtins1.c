/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:01:06 by pmontese          #+#    #+#             */
/*   Updated: 2022/02/23 18:37:39 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

int	is_valid_identifier(char *arg, int allow_equalsign)
{
	int	i;

	if (isvalidchar4var(arg[0], 1))
	{
		i = 1;
		while (isvalidchar4var(arg[i], 0))
			i++;
		if (allow_equalsign && (arg[i] == '=' || arg[i] == 0))
			return (1);
		if (!allow_equalsign && arg[i] == 0)
			return (1);
	}
	return (0);
}

void	bi_export(t_command *cmd, t_param *param, int is_child)
{
	int		i;
	int		j;
	char	*arg;

	i = 1;
	if (cmd->argc == 1 && is_child)
	{
		print_export(param);
		return ;
	}
	while (i < cmd->argc && !is_child && param->cmdc == 1)
	{
		arg = cmd->argv[i];
		if (!is_valid_identifier(arg, 1))
		{
			printf("minishell: export: '%s': not a valid identifier\n", arg);
			g_status = 1;
			i++;
			continue ;
		}
		set_env_var(get_keyval(arg), param);
		i++;
	}
}

int	bi_pwd(int ischild)
{
	char	*buf;

	if (!ischild)
		return (0);
	buf = getcwd(NULL, 0);
	ft_putstr(buf);
	ft_putstr("\n");
	free(buf);
	return (0);
}
