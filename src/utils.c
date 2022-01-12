/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <lvintila@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:22:27 by lvintila          #+#    #+#             */
/*   Updated: 2022/01/10 19:52:38 by lvintila         ###   ########.fr       */
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
	//	exit(1);
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
	printf("rl_gets\n");
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

//int	redirection(t_param *param, char *av[], char **args, char **env)
/* int		redirection(t_param *param, char **env) */
/* {
	int		i;
	int		exec_counter = 0; */
//	int		fd;
//	char	*aux;

	/* param->dir = 0;
	i = 0;
 	printf("param->aux inicial en redirection is %s\n", param->aux);
	while (param->aux[i])
	{
 		printf("param->aux in loop redirection is %s\n", param->aux);
		if (param->aux[i] == '<')
		{
			param->indir++; */
		//	param->indir_cmd = args[i + 1];
		//	param->indir_cmd = (aux + 1); 
		//	printf("found <, param->indir_cmd es: %s\n", param->indir_cmd);
/* 		}
		if (param->aux[i] == '>')
		{
			param->dir++; */
		//	param->dir_cmd = args[i + 1];
		//	printf("found >, param->dir_cmd es: %s\n", param->dir_cmd);
		/* } */
		//printf("args[%d]: %s\n", i, args[i]);
	/* 	i++;
	}
 	printf("param->aux after loop is %s\n", param->aux);
	printf("REDIRECTION: param->dir is: %d\n", param->dir);
	if (param->dir == 1)
	{
		printf("1\n");
		param->fd = open(param->dir_cmd, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		printf("2\n");
		if (!param->fd)
			exit (-1);
		printf("3\n");
		dup2(param->fd, 1);
		printf("4\n"); */
		//if ((execve(param->aux, (&args[1]), env)) == -1)
		//	check_str(param->aux, args[1]);
 	/* 	new_process(&param->cmds[0], exec_counter, env); */
/*		if (access(param->cmds[0], F_OK) == 0)
		{
			file = param->cmds[0];
		}
		else
			(file = find_path(param->cmds[0] ,env));
		if (file)
		{
			child_pid = fork();
			if (child_pid == 0)
			{
				if ((execve(file, (&param->cmds[0]), env)) == -1)
				{
					check_str(file, param->cmds[0]);
				}
			}
			waitpid(child_pid, &status, 0);
		}
		else
		{
			perror("Error");
			return (127);
		} *//* 
		printf("param->dir_cmd in redirection is: %s\n", param->dir_cmd); */
	//	printf("args[1] in redirection is: %s\n", args[1]);
/* 		printf("param->aux in redirection is: %s\n", param->aux);
		dup2(0, 1);
		close(param->fd); */
/* 	}
	else if (param->dir == 2)
	{
		param->fd = open(param->dir_cmd, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (!param->fd)
			exit (-1);
		dup2(param->fd, 1);
 		new_process(param->cmds, exec_counter, env);
		dup2(0, 1);
		close(param->fd);
	}
	return(1);
}

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