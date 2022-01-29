/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:55:41 by lvintila          #+#    #+#             */
/*   Updated: 2022/01/29 14:14:41 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

/* busca si hay una variable con el mismo nombre y cambia su valor
si no lo hay devuelve 0*/
int		try_set_existing_var(t_keyval *var, t_param *param)
{
	int	i;

	i = 0;
	while (i < param->envc)
	{
		if (!ft_strcmp(var->key, param->env[i]->key))
		{
			free(var->key); // usamos el key que ya existe
			free(param->env[i]->val); // usamos el val nuevo
			param->env[i]->val = ft_strdup(var->val);
			return (1);
		}
		i++;
	}
	return (0);
}

/* Damos por hecho que key y value están en el heap*/
void	set_env_var(t_keyval *var, t_param *param)
{
	int i;
	t_keyval **new_env;

	if (!try_set_existing_var(var, param)) // si no existe la variable
	{
		// actualiza env
		new_env = (t_keyval**)(malloc(sizeof(t_keyval*) * (param->envc + 1)));
		i = 0;
		while (i < param->envc)
		{
			new_env[i] = param->env[i];
			i++;
		}
		new_env[i] = var;
		if (param->env != NULL)
			free(param->env);
		param->env = new_env;
		param->envc++;
	}
}

void	read_env(t_param *param, char **env)
{
	int	i;
	int j;
	t_keyval *keyval;

	i = 0;
	while (env[i] != NULL)
	{
		keyval = get_keyval(env[i]);
		set_env_var(keyval, param);
		i++;
	}
	// test print env
	bi_env(param);
}

void 	init_params(t_param *param, char **env)
{
	int	i;
	int j;
	char	key[1000];

	param->line				= NULL;
	param->tmp_in			= 0;
	param->tmp_out			= 0;
	param->fd_in			= 0;
	param->fd_out			= 0;
	param->cmds				= 0;
	//crea el env tipo keyval
	param->envc				= 0;
	param->env				= NULL;
	read_env(param, env);
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

void	myshell_nointerac(char *script, char **env)
{
	int		fd;
	char	*doc;
	t_param		*param;
	t_token		*tokens;
	t_command	**commands;

	if (isdir(script))
	{
		printf("%s: is a directory \n", script);
		errno = 126;
		exit(126);
	}

	// TODO comprobar permisos

	doc = read_script(script);
	printf("file content:\n%s\n", doc);

	tokens = tokenizer(doc);
	commands = parser(tokens);
	// executer(env, tokens, commands);
	cmd_execute(commands, param, env);
	free(doc);
	// free tokens
	// free commands
	exit(0);
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
	init_params(param, env);
	printf("Entering interactive mode\n");
	status = myshell_loop(param, av, execution_coun, env);
	return (status);
}
