/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:27:05 by pmontese          #+#    #+#             */
/*   Updated: 2022/02/23 19:35:36 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"
#define DEBUG 0
#define STX_ERR 1
#define CMD_CPT 2

int	parse_redir(t_token *tkn, t_token *nxt, t_command *cmd, int *pos)
{
	int	ot;

	ot = tkn->op_type;
	if (ot == OT_ORED || ot == OT_IRED || ot == OT_ORED2 || ot == OT_HEREDOC)
	{
		if (nxt->type != TT_WORD)
			return (EXIT_FAILURE);
		if (ot == OT_ORED || ot == OT_ORED2)
			add_fileout(cmd, nxt, ot);
		if (ot == OT_ORED2)
			cmd->append = 1;
		if (ot == OT_IRED)
		{
			cmd->filein = nxt->cnt;
			cmd->fileintkn = nxt;
		}
		if (ot == OT_HEREDOC)
		{
			cmd->hdocword = nxt->cnt;
			cmd->hdoctkn = nxt;
		}
		*pos = *pos + 1;
	}
	return (EXIT_SUCCESS);
}

int	do_token(t_token *tkn, t_token *nxt, t_command *cmd, int *pos)
{
	if (tkn->op_type == OT_PIPE && cmd->name == NULL || \
	parse_redir(tkn, nxt, cmd, pos))
	{
		my_perror(SYNTAX_ERR, tkn->cnt, 2);
		return (STX_ERR);
	}
	if (tkn->op_type == OT_PIPE && cmd->name != NULL)
	{
		cmd->piped = 1;
		*pos = *pos + 1;
		return (CMD_CPT);
	}
	if (tkn->type == TT_WORD && cmd->name != NULL)
		argv_append(cmd, tkn);
	if (tkn->type == TT_WORD && cmd->name == NULL)
	{
		cmd->name = tkn->cnt;
		cmd->argv[0] = (char *)(tkn->cnt);
		cmd->arglst = ft_lstnew(tkn);
		cmd->argc = 1;
	}
	return (0);
}

int	get_command(t_list *tokens, t_command *cmd, t_param *param)
{
	static int	pos = 0;
	t_token		*tkn;
	t_token		*nxt;
	int			res;

	tkn = (t_token *)(ft_lstat(tokens, pos)->content);
	nxt = (t_token *)(ft_lstat(tokens, pos + 1)->content);
	while (tkn && tkn->type != TT_EOF)
	{
		res = do_token(tkn, nxt, cmd, &pos);
		if (res == STX_ERR)
		{
			pos = 0;
			param->syntx_err = 1;
			return (0);
		}
		if (res == CMD_CPT)
			return (1);
		pos++;
		tkn = (t_token *)(ft_lstat(tokens, pos)->content);
		nxt = NULL;
		if (ft_lstat(tokens, pos + 1))
			nxt = (t_token *)(ft_lstat(tokens, pos + 1)->content);
	}
	return (pos = 0);
}

t_list	*parser(t_list *tknlst, t_param *param)
{
	t_list		*cmd_lst;
	t_list		*tmp;
	t_command	*cmd;
	int			max_args;
	int			i;

	max_args = ft_lstsize(tknlst);
	cmd = new_command(max_args);
	cmd_lst = ft_lstnew(cmd);
	tmp = cmd_lst;
	while (get_command(tknlst, (t_command *)tmp->content, param))
	{
		cmd = new_command(max_args);
		ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
		tmp = tmp->next;
	}
	param->cmdc = ft_lstsize(cmd_lst);
	return (cmd_lst);
}
