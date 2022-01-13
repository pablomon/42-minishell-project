/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <lvintila@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 20:54:21 by lvintila          #+#    #+#             */
/*   Updated: 2022/01/13 19:18:21 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	*str;
	char	**tab;

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

void	child1(int fd[2], int f1, char **argv, char **envp)
{
	char	**cmd;
	char	*str;

	close(fd[0]);
	if (f1 < 0 )
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, "\n", 1);
		exit(1);
	}
	dup2(f1, STDIN);
	close(f1);
	dup2(fd[1], STDOUT);
	close(fd[1]);
	cmd = ft_split(argv[2], ' ');
	str = find_path(cmd[0], envp);
	if (execve(str, cmd, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		write(2, argv[2], ft_strlen(argv[2]));
		write(2, "\n", 1);
		free_arr(cmd);
		free(str);
	}
}

void	parent1(int fd[2], int f2, char **argv, char **envp)
{
	char	**cmd;
	char	*str;

	close(fd[1]);
	dup2(fd[0], STDIN);
	close(fd[0]);
	dup2(f2, STDOUT);
	cmd = ft_split(argv[3], ' ');
	str = find_path(cmd[0], envp);
	if (execve(str, cmd, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		write(2, argv[3], ft_strlen(argv[3]));
		write(2, "\n", 1);
		free_arr(cmd);
		free(str);
	}
}

void	pipex(int f1, int f2, char **argv, char **envp)
{
	pid_t	parent;
	int		fd[2];

	pipe(fd);
	parent = fork();
	if (parent < 0)
		return (perror("Error"));
	 else if (parent == 0)
		parent1(fd, f2, argv, envp);
	else
	{
		parent = fork();
		if (parent < 0)
			return (perror("Error"));
		if (parent == 0)
			child1(fd, f1, argv, envp);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(parent, NULL, 0);
}

int	m_pipex(int argc, char **argv, char **envp)
{
	int	f1;
	int	f2;

	if (argc == 5)
	{
		f1 = open(argv[1], O_RDONLY);
		f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (f2 < 0)
		{
			write(2, "pipex: no such file or directory: ", 34);
			write(2, argv[4], ft_strlen(argv[4]));
			write(2, "\n", 1);
			exit(1);
		}
		pipex(f1, f2, argv, envp);
	}
	else
	{
		write(2, "use pipex: ./pipex infile command1 command2 outfile\n", 52);
		exit(1);
	}
	return (0);
}
