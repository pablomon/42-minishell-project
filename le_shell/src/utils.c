/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <lvintila@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:22:27 by lvintila          #+#    #+#             */
/*   Updated: 2021/12/27 22:12:55 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

void	check_str(char *str, char *cmd)
{
	if (access(str, F_OK) != 0)
	{	
		write(2, "command nnot found: ", 20);
		write(2, cmd, ft_strlen(cmd));
		write(2, "\n", 1);
		//free(str);
	//	free(cmd);
		exit(1);
	}
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	print_env(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		write(STDOUT_FILENO, env[i], strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

char	*rl_gets()
{
	/*
	 * * A static variable for holding the line.
	 */
	static char *line_read;
	line_read = (char *)NULL;
	/*
    ¦* If the buffer has already been allocated, return the memory
    ¦* to the free pool.
	 */
	if (line_read)
	{
		free (line_read);
		line_read = (char *)NULL;
	}
	/*
	 * Get a line from the user.
	 */
    line_read = readline ("");
	/*
	 * If the line has any text in it, save it on the history.
	 */
    if (line_read && *line_read)
		add_history (line_read);
    return (line_read);
}
