/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:57:54 by lvintila          #+#    #+#             */
/*   Updated: 2021/12/27 20:05:14 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

void print_env(char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		write(STDOUT_FILENO, env[i], strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}

char    *rl_gets()
{
	/*
	¦* A static variable for holding the line.
	*/
	static char *line_read;
	line_read = (char *)NULL;
        /*
        ¦* If the buffer has already been allocated, return the memory
        ¦* to the free pool.
        ¦*/
	if (line_read)
    {
		free (line_read);
		line_read = (char *)NULL;
    }
   
    /*
    ¦* Get a line from the user.
    */
    line_read = readline ("");
   
    /*
    ¦* If the line has any text in it, save it on the history.
	*/
	if (line_read && *line_read)
		add_history (line_read);
	return (line_read);
}
