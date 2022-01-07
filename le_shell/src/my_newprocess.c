/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_newprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:58:30 by lvintila          #+#    #+#             */
/*   Updated: 2021/12/27 22:10:49 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

/**
 * new_process - This function create a child process and executes
 * @av: Pointer to an array of strings with all arguments of input buffer
 * @exec_counter: Executions counter in each position.
 * @env: Enviroment variable.
 * Return: void
 **/

int new_process(char *av[], int exec_counter, char **env)
{
	char	*path = NULL;
	char	*file = NULL;
	int		status;
	pid_t	child_pid;
	char	*msg_err;

	status = 0;
	if (access(av[1], F_OK) == 0)
		file = av[1];
	else
		(file = find_path(av[1] ,env));
	if (file)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			if ((execve(file, (&av[1]), env)) == -1)
			{
				check_str(file, av[1]);
			//	msg_err = av[1];
			//	perror(msg_err);
		//		free(file);
		//		exit(1);
			}
		}
		waitpid(child_pid, &status, 0);
	}
	else
	{
		perror("Error");
		return (127);
	}
	return (0);
}

