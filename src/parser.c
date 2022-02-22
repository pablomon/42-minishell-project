/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:27:05 by pmontese          #+#    #+#             */
/*   Updated: 2022/02/22 21:26:11 by pmontese         ###   ########.fr       */
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
		*pos = *pos + 1; // move ahead 2
	}
	return (EXIT_SUCCESS);
}

int	do_token(t_token *tkn, t_token *nxt, t_command *cmd, int *pos)
{
	if (tkn->op_type == OT_PIPE && cmd->name == NULL)
	{
		my_perror(SYNTAX_ERR, tkn->cnt, 2);
		return (STX_ERR);
	}
	if (tkn->op_type == OT_PIPE && cmd->name != NULL)
	{
		cmd->piped = 1;
		if (DEBUG)
		{
			printf("Command completed:\n");
			print_cmd(cmd);
		}
		*pos = *pos + 1;
		return (CMD_CPT);
	}
	if (parse_redir(tkn, nxt, cmd, pos))
	{
		my_perror(SYNTAX_ERR, tkn->cnt, 2);
		return (STX_ERR);
	}
	if (tkn->type == TT_WORD && cmd->name != NULL)
		argv_append(cmd, tkn);
	if (tkn->type == TT_WORD && cmd->name == NULL)
	{
		cmd->name = tkn->cnt;
		cmd->argv[0] = (char*)(tkn->cnt);
		cmd->arglst = ft_lstnew(tkn);
		cmd->argc = 1;
	}
	return (0);
}

int	get_command(t_list *tokens, t_command *cmd, t_param *param)
{
	static int	pos = 0;
	if (DEBUG)
		printf("\nNew command ( token %d )\n", pos);
	t_token		*tkn;
	t_token		*nxt;
	int			res;

	tkn = NULL;
	nxt = NULL;
	// if (ft_lstat(tokens, pos))
		tkn = (t_token*)(ft_lstat(tokens, pos)->content);
	// if (ft_lstat(tokens, pos + 1))
		nxt = (t_token*)(ft_lstat(tokens, pos + 1)->content);
	if (DEBUG)
	{
		if (tkn && tkn->type != TT_EOF)
			printf("tkn cnt (pos %d): %s\n", pos, tkn->cnt);
		if (nxt && nxt->type != TT_EOF)
			printf("nxt cnt (pos %d): %s\n", pos + 1, nxt->cnt);
	}
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
		tkn = NULL;
		nxt = NULL;
		tkn = (t_token*)(ft_lstat(tokens, pos)->content);
		if (ft_lstat(tokens, pos + 1))
			nxt = (t_token*)(ft_lstat(tokens, pos + 1)->content);
	}
	if (DEBUG)
	{
		printf("Command completed:\n");
		print_cmd(cmd);
	}
	pos = 0;
	return (0);
}

t_list	*parser(t_list *tknlst, t_param *param)
{
	t_list		*cmd_lst;
	t_list		*tmp;
	t_command	*cmd;
	int			max_args;
	int			i;

	if (DEBUG)
		printf("\nLIST PARSER----\n");
	max_args = ft_lstsize(tknlst);
	cmd = new_command(max_args);
	cmd_lst = ft_lstnew(cmd);
	tmp = cmd_lst;
	while (get_command(tknlst, (t_command*)tmp->content, param))
	{
		cmd = new_command(max_args);
		ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
		tmp = tmp->next;
	}
	param->cmdc = ft_lstsize(cmd_lst);
	if (DEBUG)
	{
		printf("Printing parser results ( %d commands )\n", param->cmdc);
		tmp = cmd_lst;
		i = 0;
		while (tmp)
		{
			printf("Command %d:\n", i);
			print_cmd(tmp->content);
			printf("\n");
			tmp = tmp->next;
			i++;
		}
		printf("Parser finished\n");
	}
	return cmd_lst;
}
