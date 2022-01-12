/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <lvintila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:19:40 by lvintila          #+#    #+#             */
/*   Updated: 2022/01/09 12:56:56 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

int args_length(char **args)
{
	int i;

    i = 0;
	while(args[i] != NULL)
	{
		i++;
	}
	return (i);
}

int   re_direction_and_pipe(char **args, char **env)
{
   	/*saving current stdin and stdout for restoring*/
	int     temp_in;			
	int     temp_out;			
	int     j; 
    int     i; 
    int     flag;
	int     fdin;
    int     fdout;
    char    **rargs;
    char    *file;
 
    temp_in = dup(0);
    temp_out = dup(1);
    flag = 0;
    fdin = 0;
    j = 0;
    while(j < args_length(args))
    {
        if(ft_strcmp(args[j], "<") == 0)
        {
            fdin = open(args[j + 1], O_RDONLY | O_CREAT | O_TRUNC, 0664);
            flag += 2;
        }
        j++;
    }
    if (!fdin)
        fdin = dup(temp_in);
    int pid;
    i = 0;
    while (i < (args_length(args) - flag))
    {
        rargs = split_line(args[i]);
        printf("i es: %d - rargs[0] is: %s\n", i, rargs[0]);
        dup2(fdin, 0);
        close(fdin);
        if (i == args_length(args) - 3 && ft_strcmp(args[i + 1], ">") == 0)
        {
            if ((fdout = open(args[i + 2], O_WRONLY | O_CREAT | O_TRUNC, 0664)))
                i++;
        }
        else if (i == args_length(args) - flag - 1)
            fdout = dup(temp_out);
        else
		{
			int fd[2];
			pipe(fd);
			fdout = fd[1];
			fdin = fd[0];
		}
		dup2(fdout, 1);
		close(fdout);
        pid = fork();
        if (pid == 0)
        {
            execvp(rargs[0], rargs);
            perror("error forking\n");
			exit(EXIT_FAILURE);
        }

		wait(NULL);
        i++;
    }
    dup2(temp_in, 0);
    dup2(temp_out, 1);
    close(temp_in);
    close(temp_out);
    return (1);
}