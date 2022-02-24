/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:49:01 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/23 23:02:02 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

void	bi_exit_child(t_command *cmd, t_param *param, int cmd_num)
{
	if (param->cmdc == 1)
		return ;
	g_status = 130;
	if (cmd->argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_status = 1;
	}
	else if (cmd->argc == 2)
	{
		g_status = ft_atoi(cmd->argv[1]);
		if (g_status == 0)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			g_status = 255;
		}
	}
}

void	check_num_arg(t_command *cmd)
{
	g_status = ft_atoi(cmd->argv[1]);
	if (g_status == 0)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_status = 255;
	}
}

void	bi_exit_parent(t_command *cmd, t_param *param, int cmd_num)
{
	int		isexit;

	if (cmd_num != 0)
		return ;
	isexit = 1;
	g_status = 0;
	if (param->cmdc == 1)
		ft_putendl_fd("exit", 2);
	else
		isexit = 0;
	if (cmd->argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_status = 1;
		isexit = 0;
	}
	else if (cmd->argc == 2)
		check_num_arg(cmd);
	if (isexit)
	{
		cleanup(param);
		exit(g_status);
	}
}

void	bi_unset_aux(char *arg, t_param *param)
{
	int	j;

	j = 0;
	while (j < param->envc)
	{
		if (ft_strcmp(arg, param->env[j]->key) == 0)
		{
			unset_env_var(arg, param);
			break ;
		}
		j++;
	}
}

void	bi_unset(t_command *cmd, t_param *param, int ischild)
{
	int		i;
	char	*arg;

	i = 1;
	if (ischild)
		return ;
	while (i < cmd->argc && param->cmdc == 1 && !ischild)
	{
		arg = cmd->argv[i];
		if (!is_valid_identifier(arg, 0))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", arg);
			g_status = 1;
			i++;
			continue ;
		}
		bi_unset_aux(arg, param);
		i++;
	}
}
