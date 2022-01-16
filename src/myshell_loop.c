/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:58:38 by lvintila          #+#    #+#             */
/*   Updated: 2022/01/16 12:55:34 by pmontese         ###   ########.fr       */
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
	param->line = rl_gets();
	if (param->line != NULL)
		return (0);
	// printf("get_cmd: param->line is: %s\n", param->line);
	else
	{
		perror("Error get_cmd: ");
		return (-1);
	}
}

int myshell_loop(t_param *param, char *av[], int exec_count, char **env)
{
	int		interactive;
	int		process_status;
	int		i;
	int		read;
	t_token     *tokens;
	t_command   **commands;

	interactive = 1;
	process_status = 0;
	if (isatty(STDIN_FILENO) == 0)
		interactive = 0;
	i = 0;
	while (1)
	{
		if (interactive == 1)
			write(STDIN_FILENO, "($) ", 4);
		read = get_cmd(param);

		// exit condition
		if (read == EOF)
		{
			free(param->line);
			write(STDIN_FILENO, "\n", 1);
			return (0);
		}

		if (read == 0)
		{
			tokens = tokenizer(param->line);
			commands = parser(tokens);
			executer(env, tokens, commands);
			free(param->line);
			// free tokens
			// free commands
		}
		exec_count++;
	}
//	close(param->fd);
	free(param->line);
	return (0);
}
