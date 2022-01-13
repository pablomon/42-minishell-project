/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <lvintila@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:22:27 by lvintila          #+#    #+#             */
/*   Updated: 2022/01/13 20:03:57 by lvintila         ###   ########.fr       */
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
	//	free(str);
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


int	found_op(char *str, char *op)
{
	int i;

	i = 0;
	while (*str++ != '\0')
	{
		if (str == op)
		{
			printf("found_op say: \"found op\" ...\n");
			return (0);
		}
	}
	return (1);
}

int	found_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == c)
		{
			printf("found_char say: \"found\" > ...\n");
			return (0);
		}
	}
	return (1);
}

 int		redirection(t_command **commands, char **env)
 {
	int		i;
	int		exec_counter = 0;
	t_param *param;

	i = 0;
	param = malloc(sizeof(t_param));
	while (commands[i] != NULL)
	{
		if (commands[i]->fileout != NULL && commands[i]->append == 0)
		{
			param->fd = open(commands[i]->fileout, O_CREAT | O_RDWR | O_TRUNC, 0664);
			if (!param->fd)
				perror("Error:");
				//printf("4\n");
 			dup2(param->fd, 1);
		//	dup2(1, 1);
		//	new_process(commands, exec_counter, env);
/* 			close(1);
		//	dup2(0, 1);
			dup(1);
			dup(0);
			dup(param->fd); */
		//	close(param->fd);
		}
		else if (commands[i]->append != 0)
		{
			param->fd = open(commands[i]->fileout, O_CREAT | O_WRONLY | O_APPEND, 0664);
			if (!param->fd)
				perror("Error:");
			dup2(param->fd, 1);
/* 			printf("4\n");
			new_process(commands, exec_counter, env);
			dup2(0, 1);
			close(param->fd); */
		}
		else if (commands[i]->filein != NULL)
		{
			param->fd = open(commands[i]->filein, O_RDONLY);
			if (!param->fd)
				perror("Error:");
			close(0);
			dup2(param->fd, 0);
			//close(param->fd);
		}
		i++;
 	}
	return(0); 
}


/* 
int	exec_cmds(t_param *param, char **cmds, int exec_count, char **env)
{
	if (cmds[1])
		param->process_status = new_process(cmds, exec_count, env);
	return (0);
}
 */


void    redirect(char *buff)
{
	int		redirect_flag;
	// times of ">" 
	char	*redirect_file;
	int		fd;
	char	*ptr;

	ptr = buff;
	free(buff);
    redirect_flag = 0;
    redirect_file = NULL;
	while(*ptr != '\0')
	{
		if(*ptr == '>')
		{
			ptr++;
			++redirect_flag;
			// Si este bit es>, la cuenta se incrementa en uno y este bit 
			// se reescribe como \0 para evitar que se interprete
			// como un comando

			if(*ptr == '>')
			{
				++redirect_flag;
				ptr++;
			}
			
			while(*ptr == ' ' && *ptr != '\0')
			{
				ptr++;
			}

			redirect_file = ptr;
			// Después de la detección >>, el siguiente es el nombre del
			// archivo redirigido, que será analizado
			
			while(*ptr != ' ' && *ptr != '\0')
			{
				ptr++;
			}				
			*ptr = '\0';
		}
		ptr++;
	}
}