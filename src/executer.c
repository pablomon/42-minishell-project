/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:49:42 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/25 01:05:23 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

void	set_status(int status)
{
	g_status = status % 255;
	if (status == 2)
		g_status = 130;
	else if (status == 3)
		g_status = 131;
}

int	do_pipe(t_param *param, t_command *cmd, int i)
{
	pid_t	pid;
	int		status;
	int		fds[2];

	pipe(fds);
	reg_child_signals();
	pid = fork();
	if (pid < 0)
	{
		my_perror(FORK_ERR, NULL, 1);
		g_status = 1;
		return (g_status);
	}
	if (pid == 0)
		execute_child(cmd, param, i, fds);
	waitpid(pid, &status, 0);
	reg_parent_signals();
	dup2(fds[READ_END], param->fd_in);
	close(fds[WRITE_END]);
	close(fds[READ_END]);
	set_status(status);
	return (g_status);
}

void	close_fds(t_param *param)
{
	close(param->fd_in);
	close(param->fd_out);
	dup2(param->default_in, STDIN_FILENO);
	dup2(param->default_out, STDOUT_FILENO);
	close(param->default_in);
	close(param->default_out);
}

void	set_initial_input(t_param *param)
{
	param->default_in = dup(STDIN_FILENO);
	param->default_out = dup(STDOUT_FILENO);
	param->fd_in = STDIN_FILENO;
}

int	cmd_execute(t_list *cmd_list, t_param *param)
{
	int			i;
	t_command	*cmd;

	i = 0;
	set_initial_input(param);
	while (cmd_list)
	{
		cmd = (t_command *)cmd_list->content;
		update_command_args(cmd, param);
		if (open_redirections(cmd, param, cmd->fileouts) || !cmd->argv[0])
		{
			i++;
			cmd_list = cmd_list->next;
			continue ;
		}
		do_pipe(param, cmd, i);
		if (!try_bis(cmd, param, 0, i))
			if (ft_strcmp(cmd->argv[0], "exit") == 0)
				bi_exit_parent(cmd, param, i);
		i++;
		cmd_list = cmd_list->next;
		system("leaks minishell");
	}
	close_fds(param);
	return (g_status);
}
