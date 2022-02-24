/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:22:27 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/23 23:59:26 by lvintila         ###   ########.fr       */
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

char	**path_envp(char **envp)
{
	int		i;
	char	**tab;

	if (!tab && !tab[0])
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			tab = ft_split(ft_strchr(envp[i], '/'), ':');
			break ;
		}
	}
	return (tab);
}

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	*str;
	char	*tmp;
	char	**tab;

	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
		return (cmd);
	tab = path_envp(envp);
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
	static char	*line_read;

	line_read = NULL;
	if (line_read)
	{
		free (line_read);
		line_read = NULL;
	}
	line_read = readline(param->prompt);
	if (line_read && *line_read)
		add_history (line_read);
	return (line_read);
}
