/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:22:27 by lvintila          #+#    #+#             */
/*   Updated: 2022/01/30 13:15:27 by pmontese         ###   ########.fr       */
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

char	*find_path(char *cmd, t_param *param)
{
	int		i;
	char	*str;
	char	**tab;
	char	**envp;

	envp = make_envp(param);
 	//TODO cambiar la función para que no utilize envp, si no directamente param->env
	if (access(cmd, F_OK) == 0)
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
		str = ft_strjoin(ft_strjoin(tab[i], "/"), cmd);
		if (access(str, F_OK) == 0)
			return (str);
	}
	check_str(str, cmd);
	return (cmd);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
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