/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:58:38 by lvintila          #+#    #+#             */
/*   Updated: 2022/01/28 21:34:40 by pmontese         ###   ########.fr       */
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

int	ft_arr_len(char **arr)
{
	int	i;
	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

void set_var(char *name, char *value, t_param *param)
{
	int	i;
	t_keyvalue **vars_new;
	t_keyvalue **tmp;

	vars_new = (t_keyvalue**)(malloc(sizeof(t_keyvalue*) * (param->num_vars + 2)));
	i = 0;
	while (i < param->num_vars)
	{
		vars_new[i] = param->variables[i];
		i++;
	}
	vars_new[i] = (t_keyvalue*)(malloc(sizeof(t_keyvalue)));
	vars_new[i]->key = name;
	vars_new[i]->value = value;

	// TODO no liberar si null
	tmp = param->variables;
	param->variables = vars_new;
	free(tmp);
	param->num_vars++;
}

int	assignment_check(t_param *param)
{
	char *clean_line;
	char *name;
	char *value;
	char **split_res;
	int i;

	split_res = ft_split(param->line, ' ');
	if (split_res == NULL || ft_arr_len(split_res) != 1)
		return 0;
	clean_line = ft_strtrim(param->line, " \t");
	if (!ft_isalpha(*clean_line))
		return 0;
	i = 0;
	while(ft_isalnum(clean_line[i]))
	{
		name[i] = clean_line[i];
		i++;
	}
	name[i] = '\0';
	if (clean_line[i] != '=')
		return 0;

	i++;
	value = &clean_line[i];
	printf("name: %s\n", name);
	set_var(name, value, param);
	return 1;
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

		if (assignment_check(param))
		{
			ft_putstr("----\n");
			return 0;
		}
		if (param->num_vars > 0)
		{
			printf("key = %s, value = %s\n", param->variables[0]->key, param->variables[0]->value);
		}

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
