/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:55:41 by lvintila          #+#    #+#             */
/*   Updated: 2022/01/12 20:38:47 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

void 	init_params(t_param *param)
{
	param->line			= NULL;
	param->token		= NULL;
	param->exec_count	= 0;
	param->dir			= 0;
	param->dir_cmd		= NULL;
	param->aux			= NULL;
	param->fd			= 0;
	param->indir		= 0;
}

int	filetest(const char *path)
{
	if (access(path, F_OK) == -1)
	{
		printf("errno %d\n", errno);
		exit(0);
	}
}
int isdir(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

void	myshell_nointerac(char *script, char **env)
{
	int		fd;
	char	*total;
	char	*line;
	char	*tmp;

	if (isdir(script))
	{
		printf("%s: is a directory \n", script);
		exit(126);
	}
	if (access(script, F_OK) == -1)
	{
		printf("%s: No such file or dir\n", script);
		exit(127);
	}

	// TODO comprobar permisos

	fd = open(script, O_RDONLY);
	if (fd < 0)
		exit (fd);
	total = ft_strdup("");
	if (get_next_line(fd, &line))
	{
		tmp = total;
		total = ft_strjoin(total, line);
		free(tmp);
		free(line);
	}
	while (get_next_line(fd, &line))
	{
		tmp = total;
		total = ft_strjoin(total, "\n");
		free(tmp);
		tmp = total;
		total = ft_strjoin(total, line);
		free(tmp);
		free(line);
	}
	printf("file content:\n%s\n", total);

	exit(1);
}

int main(int ac, char *av[], char **env)
{
	t_param *param;
	int execution_coun = 1;
	int status = 0;

	param = malloc(sizeof(t_param));
	if (ac > 2)
	{
		write(2, "Error: wrong number of arguments\n", 33);
		write(2, "Usage: './minishell' or './minishell file'\n", 43);
		return (1);
	}
	param->script = NULL;
	if (ac == 2)
	{
		printf("Non interactive mode\n");
		// if (isatty(STDIN_FILENO) == 0) {	}
		myshell_nointerac(av[1], env);
	}
	printf("Entering interactive mode\n");
//	param->dir_cmd = NULL;
//	param->line = NULL;
	// printf("main 0\n");
//	init_params(param);
	// printf("main 1\n");
	status = myshell_loop(param, av, execution_coun, env);
	printf("main 2\n");
	return (status);
}
