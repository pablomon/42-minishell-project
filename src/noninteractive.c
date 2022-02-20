/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noninteractive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:50:44 by pmontese          #+#    #+#             */
/*   Updated: 2022/02/04 20:50:45 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

/*	NO INTERACTIVO
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

void	myshell_nointerac(char *script, t_param *param, char **env)
{
	int		fd;
	char	*doc;
	t_token		*tokens;
	t_command	**commands;
	t_keyval	*keyval;

	if (isdir(script))
	{
		printf("%s: is a directory \n", script);
		errno = 126;
		exit(126);
	}

	// TODO comprobar permisos
	doc = read_script(script);
	printf("file content:\n%s\n", doc);

	tokens = tokenizer(doc, param);
	commands = parser(tokens);
	// executer(env, tokens, commands);
	cmd_execute(commands, param);
	free(doc);
	// free tokens
	// free commands
	exit(0);
}
*/
