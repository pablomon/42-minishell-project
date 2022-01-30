/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:58:38 by lvintila          #+#    #+#             */
/*   Updated: 2022/01/30 12:54:48 by pmontese         ###   ########.fr       */
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

	// param->line = rl_gets();
	rawline = rl_gets();
	i = 0;
	if (rawline != NULL)
	{
		// Limpiar el principio del input de espacios
		while (ft_isspace(rawline[i]))
			i++;
		param->line = ft_strdup(&rawline[i]);
		free(rawline);
		// Si después de limpiar todavía hay algo devuelve 1
		if (*param->line != 0)
			return (1);
		// Si la linea está vacía devuelve 0
		return (0);
	}
	else
	{
		perror("Error get_cmd: ");
		return (-1);
	}
}

void	clean_tokens(t_token *tkns)
{
	int	i;

	i = 0;
	while (tkns[i].type != TT_EOF)
	{
		free(tkns[i].cnt);
		i++;
	}
}

int myshell_loop(t_param *param, char *av[], int exec_count)
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
		// si la linea tiene contenido
		if (read)
		{
			tokens = tokenizer(param->line, param);
			commands = parser(tokens);
			i = 0;
			while (commands[i] != NULL)
				i++;
			param->cmds = i++;
			free(param->line);
			cmd_execute(commands, param);

			clean_tokens(tokens);
			free(tokens);
			free(commands);
		}
		else
			ft_putstr("\n");
		exec_count++;
	}
//	close(param->fd);
	free(param->line);
	return (0);
}
