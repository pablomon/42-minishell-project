/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:58:38 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/22 22:50:31 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

/**
 * get_cmd - reads command line;
 * myshell_loop - reads the command line a through readline from rl_gets()
 * and determine the mode either interactive or non-interactive from the
 * command line.
 * loops infinitely and wait for input from user
 * @av: Pointer to arrays of string
 * @execution_counter: command execution counter.
 * @env: Enviroment variable.
 * @line: extern char variable to store the input.
 * Return: status value.
 **/

int	get_cmd(t_param *param)
{
	char	*rawline;
	int		i;

	rawline = rl_gets(param);
	i = 0;
	if (rawline != NULL)
	{
		while (ft_isspace(rawline[i]))
			i++;
		param->line = ft_strdup(&rawline[i]);
		free(rawline);
		if (*param->line != 0)
			return (1);
		return (0);
	}
	else
	{
		write(1, "exit", 4);
		return (EOF);
	}
}

void	init_loop(t_param *param)
{
	param->tkn_lst = get_tokens(param->line, param);
	param->cmd_lst = parser(param->tkn_lst, param);
	if (!param->syntx_err)
	{
		expand_tokens(param->tkn_lst, param);
		g_status = cmd_execute(param->cmd_lst, param);
	}
	param->syntx_err = 0;
	free_tokens(param->tkn_lst);
	param->tkn_lst = NULL;
	free_commands(param->cmd_lst);
	param->cmd_lst = NULL;
}

int	myshell_loop(t_param *param, char *av[])
{
	int			read;
	t_token		*tokens;
	t_command	**commands;

	while (1)
	{
		read = get_cmd(param);
		if (read == EOF)
		{
			write(STDIN_FILENO, "\n", 1);
			return (0);
		}
		if (read)
			init_loop(param);
		free(param->line);
		param->line = NULL;
	}
	return (g_status);
}
