/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:55:41 by lvintila          #+#    #+#             */
/*   Updated: 2022/01/16 10:43:23 by pmontese         ###   ########.fr       */
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

int	isdir(const char *path) {
	struct stat statbuf;
	if (stat(path, &statbuf) != 0)
		return 0;
	return S_ISDIR(statbuf.st_mode);
}

char	*read_script(char *script)
{
	int		fd;
	char	*tmp;
	char	*total;
	char	*line;

	if ((fd = open(script, O_RDONLY)) < 0)
	{
		perror("error: ");
		exit (fd);	// TODO comprobar que error devuelve bash en este caso
	}
	ft_putstr("-----------");
	if (get_next_line(fd, &line))
	{	
		tmp = ft_strdup("");
		total = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
	}
	while (get_next_line(fd, &line))
	{
		tmp = total;
		total = ft_strjoin(total, "\n");
		free(tmp);
		tmp = total;
		total = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
	}
	return total;
}

int	builtins(t_command *cmd, char **env)
{
	int	is_builtin;
	char *n;
	
	n = cmd->name;
	if (!ft_strcmp(n, "exit"))
	{
		exit(1);
	}
	else if (!ft_strcmp(n, "env"))
	{
		print_env(env);
		return (1);
	}
	return (0);
}

void	executer(char *doc, char **env)
{
	t_token		*tokens;
	t_command	**cmd_lst;
	int			i;
	int			exec_count;

	tokens = tokenizer(doc);
	cmd_lst = parser(tokens);

	i = 0;
	exec_count = 0;
	while (cmd_lst[i] != NULL)
	{
		if (!builtins(cmd_lst[i], env))
		{
			redirection(cmd_lst, env);
			new_process(cmd_lst[i], exec_count, env);
			if (cmd_lst[i]->fileout)
			{
				close(1);
				dup(1);
				dup(0);
			}
			dup2(1, 0);
		}
		i++;
	}
}

void	myshell_nointerac(char *script, char **env)
{
	int		fd;
	char	*content;


	if (isdir(script))
	{
		printf("%s: is a directory \n", script);
		errno = 126;
		exit(126);
	}

	// TODO comprobar permisos

	content = read_script(script);
	printf("file content:\n%s\n", content);
	executer(content, env);
	free(content);
	exit(1);
}

int main(int ac, char *av[], char **env)
{
	t_param *param;
	int execution_coun = 1;
	int status = 0;

	if (ac > 2)
	{
		write(2, "Error: wrong number of arguments\n", 33);
		write(2, "Usage: './minishell' or './minishell file'\n", 43);
		return (1);
	}
	else if (ac == 2)
	{
		printf("Non interactive mode\n");
		myshell_nointerac(av[1], env);
	}

	param = malloc(sizeof(t_param));
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
