/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:22:27 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/22 20:25:36 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

void	check_str(char *str, char *cmd, t_param *param)
{
	if (access(str, F_OK) != 0 || access(str, X_OK) != 0)
	{
		my_perror(NOCMD, cmd, 127);
		cleanup(param);
		exit (g_status);
	}
}

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	*str;
	char	*tmp;
	char	**tab;

 	//TODO cambiar la función para que no utilize envp, si no directamente param->env
	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
		return (cmd);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
	 	{
	 		tab = ft_split(ft_strchr(envp[i], '/'), ':');
	 		break ;
	 	}
	}
	i = -1;
	while (tab[++i])
	{
		tmp = ft_strjoin(tab[i], "/");
		str = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(str, F_OK) == 0)
		{
			free_arr(tab);
			return (str);
		}
		free(str);
	}
	free_arr(tab);
	return (NULL);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*rl_gets(t_param *param)
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

	// ft_putstr_fd(param->prompt, 2);
	line_read = readline(param->prompt);
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
