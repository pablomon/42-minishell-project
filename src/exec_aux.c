/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 23:10:13 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/23 23:10:46 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

int	try_bis(t_command *cmd, t_param *param, int ischild, int cmd_num)
{
	int	ret;

	ret = 1;
	if (!ft_strcmp(cmd->name, "env"))
		bi_env(param, ischild);
	else if (!ft_strcmp(cmd->name, "export"))
		bi_export(cmd, param, ischild);
	else if (!ft_strcmp(cmd->name, "unset"))
		bi_unset(cmd, param, ischild);
	else if (!ft_strcmp(cmd->name, "cd"))
		bi_cd(cmd, param, ischild);
	else if (!ft_strcmp(cmd->name, "pwd"))
		bi_pwd(ischild);
	else if (!ft_strcmp(cmd->name, "echo"))
		bi_echo(cmd, ischild);
	else
		ret = 0;
	return (ret);
}

void	check_quoted_in_ambiguos(char *str, int quoted)
{
	if (quoted == 1 && *str == '\'')
		quoted = 0;
	if (quoted == 2 && *str == '\"')
		quoted = 0;
}

int	check_ambiguous_redir(char *str)
{	
	int		i;
	char	*ptr;
	int		quoted;
	int		dquoted;

	while (*str)
	{
		if (!quoted)
		{
			if (ft_isspace(*str))
			{
				printf("%s: Ambiguous redirect\n", SHLNAME);
				g_status = 1;
				return (1);
			}
			if (*str == '\'')
				quoted = 1;
			if (*str == '\"')
				quoted = 2;
		}
		else
			check_quoted_in_ambiguos(str, quoted);
		str++;
	}
	return (0);
}

void	check_heredoc_in_redir(t_param *param, t_command *cmd)
{
	int	len;

	close(param->fd_in);
	param->fd_in = open("/tmp/minishell-heredoc-tmp", O_WRONLY
			| O_CREAT | O_EXCL | O_TRUNC, 0600);
	len = ft_strlen(cmd->hdocword);
	write(param->fd_in, cmd->hdocword, len);
	close(param->fd_in);
	param->fd_in = open("/tmp/minishell-heredoc-tmp", O_RDONLY);
	unlink("/tmp/minishell-heredoc-tmp");
}
