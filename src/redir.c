/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 23:09:48 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/23 23:09:52 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

int	redir_out(t_param *param, t_list *fileout_lst, t_fileout *fo)
{
	g_status = 1;
	if (check_ambiguous_redir(fo->file))
		return (g_status);
	if (fo->append)
	{
		if (access(fo->file, F_OK) == 0 && access(fo->file, W_OK) == -1)
		{
			my_perror(NOPERM, fo->file, 1);
			return (g_status);
		}
		else
			param->fd_out = open(fo->file, O_CREAT | O_WRONLY | O_APPEND, 0664);
	}
	else
	{
		if (access(fo->file, F_OK) == 0 && access(fo->file, R_OK) != 0)
		{
			my_perror(NOPERM, fo->file, 1);
			return (g_status);
		}
		else
			param->fd_out = open(fo->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	}
	return (g_status);
}

int	redir_in(t_param *param, t_command *cmd)
{
	g_status = 0;
	if (check_ambiguous_redir(cmd->filein))
		return (g_status);
	param->fd_in = open(cmd->filein, O_RDONLY);
	if (param->fd_in < 0)
	{
		perror("minishell");
		return (g_status);
	}
	return (g_status);
}

int	open_redirections(t_command *cmd, t_param *param, t_list *fileout_lst)
{
	t_fileout	*fo;

	if (cmd->hdocword)
		check_heredoc_in_redir(param, cmd);
	else if (cmd->filein)
		redir_in(param, cmd);
	if (fileout_lst != NULL)
	{
		while (fileout_lst)
		{
			fo = (t_fileout *)fileout_lst->content;
			redir_out(param, fileout_lst, fo);
			fileout_lst = fileout_lst->next;
		}
	}
	else
		param->fd_out = STDOUT_FILENO;
	return (0);
}

void	update_command_args(t_command *c, t_param *param)
{
	t_list		*tmp;
	int			i;
	t_fileout	*fo;

	i = 0;
	tmp = c->arglst;
	while (tmp)
	{
		c->argv[i] = ((t_token *)(tmp->content))->cnt;
		i++;
		tmp = tmp->next;
	}
	if (c->fileintkn)
		c->filein = c->fileintkn->cnt;
	tmp = c->fileouts;
	while (tmp)
	{
		fo = (t_fileout *)(tmp->content);
		fo->file = fo->filetkn->cnt;
		tmp = tmp->next;
	}
	if (c->hdoctkn)
		c->hdocword = c->hdoctkn->cnt;
	if (c->lastfileouttkn)
		c->lastfileout = c->lastfileouttkn->cnt;
}

void	execute_child(t_command *cmd, t_param *param, int cmd_num, int fds[2])
{
	char	**envp;
	char	*file;

	dup2(param->fd_in, STDIN_FILENO);
	if (param->fd_out != STDOUT_FILENO)
		dup2(param->fd_out, STDOUT_FILENO);
	else if (cmd_num != param->cmdc - 1)
		dup2(fds[WRITE_END], STDOUT_FILENO);
	close(fds[WRITE_END]);
	close(fds[READ_END]);
	envp = make_envp(param);
	file = find_path(cmd->argv[0], envp);
	if (!try_bis(cmd, param, 1, cmd_num))
	{
		if (ft_strcmp(cmd->argv[0], "exit") == 0)
			bi_exit_child(cmd, param, cmd_num);
		else if (execve(file, cmd->argv, envp) == -1)
			check_str(file, cmd->argv[0], param);
	}
	cleanup(param);
	exit(g_status);
}
