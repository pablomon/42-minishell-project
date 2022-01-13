/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:27:05 by pmontese          #+#    #+#             */
/*   Updated: 2022/01/10 20:38:13 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

void	print_cmd(t_command *cmd)
{
	int	i;

	i = 0;
	printf("name	= %s\n" ,cmd->name);
	printf("argc	= %d\n" ,cmd->argc);
	while (i < cmd->argc)
	{
		printf("argv[%d]	= %s\n" ,i, cmd->argv[i]);
		i++;
	}
	printf("in	= %s\n", cmd->filein);
	printf("out	= %s\n", cmd->fileout);
	printf("append	= %d\n", cmd->append);
	printf("heredoc word	= %s\n", cmd->hdocword);
}

t_command	*new_command()
{
	t_command *cmd;

	cmd = (t_command*)malloc(sizeof(t_command));
	cmd->argc		= 0;
	cmd->argv		= (char**)(malloc(sizeof(char**)));
	cmd->name		= NULL;
	cmd->filein		= NULL;
	cmd->fileout	= NULL;
	cmd->hdocword	= NULL;
	cmd->argc		= 0;
	cmd->append		= 0;
	return (cmd);
}

int	parse_redir(t_token tkn, t_token nxt, t_command *cmd, int *pos)
{
	int	ot;

	ot = tkn.op_type;
	if (ot == OT_ORED || ot == OT_IRED || ot == OT_ORED2 || ot == OT_HEREDOC)
	{
		if (nxt.type != TT_WORD)
		{
			printf("syntax error: unexpected token near `%s\'\n", tkn.cnt);
			return (EXIT_FAILURE);
		}
		if (ot == OT_ORED || ot == OT_ORED2)
			cmd->fileout = nxt.cnt;
		if (ot == OT_ORED2)
			cmd->append = 1;
		if (ot == OT_IRED)
			cmd->filein = nxt.cnt;
		if (ot == OT_HEREDOC)
			cmd->hdocword = nxt.cnt;
		*pos = *pos + 1; // move ahead 2
	}
	return (EXIT_SUCCESS);
}

int	get_command(t_token *tokens, t_command *cmd, int *pos)
{
	printf("\nParsing ( token %d )\n", *pos);
	t_token	tkn;
	t_token nxt;

	tkn = tokens[*pos];
	nxt = tokens[*pos + 1];
	while (tkn.type != TT_EOF && tkn.type != TT_EMPTY)
	{
		if (tkn.op_type == OT_PIPE && cmd->name == NULL)
		{
			printf("syntax error: unexpected token near `%s\'\n", tkn.cnt);
			return (0);
		}
		if (tkn.op_type == OT_PIPE && cmd->name != NULL)
		{
			printf("Command completed ( pipe ):\n");
			print_cmd(cmd);
			*pos = *pos + 1;
			return (1);
		}
		if (parse_redir(tkn, nxt, cmd, pos))
			return (0); // Syntax error
		if (tkn.type == TT_WORD && cmd->name != NULL)
		{
			cmd->argv[cmd->argc] = tkn.cnt;
			cmd->argc++;
		}
		if (tkn.type == TT_WORD && cmd->name == NULL)
		{
			cmd->name = tkn.cnt;
			cmd->argv[0] = tkn.cnt;
			cmd->argc = 1;
		}
		*pos = *pos + 1;
		tkn = tokens[*pos];
		nxt = tokens[*pos + 1];
	}
	printf("Command completed ( end ):\n");
	print_cmd(cmd);
	cmd->argv[cmd->argc + 1] = NULL;
	return (0);
}

t_command	**parser(t_token *tokens)
{
	t_command	**cmd_lst;
	int			pos;
	int			i;

	printf("\nPARSER----\n");
	cmd_lst = (t_command**)malloc(sizeof(t_command*) * 100);
	pos = 0;
	i = 0;
	cmd_lst[i] = new_command();
	while (get_command(tokens, cmd_lst[i], &pos))
	{
		i++;
		cmd_lst[i] = new_command();
	}
	return cmd_lst;
}
