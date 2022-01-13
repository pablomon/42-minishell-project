/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:58:38 by lvintila          #+#    #+#             */
/*   Updated: 2022/01/13 20:41:11 by pmontese         ###   ########.fr       */
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
    t_command   **cmd_lst;

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

		if (read == EOF)
		{
			free(param->line);
			write(STDIN_FILENO, "\n", 1);
			return (0);
		}
		else if (ft_strncmp(param->line, "exit\n", 4) == 0)
		{
			free(param->line);
			//exit(1);
			return (process_status);
		}
		else
		{
			if (ft_strncmp(param->line, "env\n", 3) == 0)
				print_env(env);
			else if (read == 0)
			{
				tokens = tokenizer(param->line);
				i = 0;
				while (i < 200)
				{
					if (tokens[i].type == TT_EOF)
					{
						printf("Token %d: EOF\n", i);
						break;
					}
					else
						printf("Token %d: '%s'\n", i, tokens[i].cnt);
					i++;
				}
				cmd_lst = parser(tokens);

				int i = 0;
				while (cmd_lst[i] != NULL)
				{
					printf("Command %d:\n", i);
					redirection(cmd_lst, env);
					print_cmd(cmd_lst[i]);
					printf("\n");
					new_process(cmd_lst, exec_count, env);
					i++;
				}
				if (cmd_lst[0]->fileout)
				{
					close(1);
					dup(1);
					dup(0);
				}
				dup2(1, 0);
			}
		}
		exec_count++;
	}
//	close(param->fd);
	free(param->line);
	return (0);
}
