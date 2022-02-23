/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:02:06 by pmontese          #+#    #+#             */
/*   Updated: 2022/02/23 19:03:29 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

void	argv_append(t_command *cmd, t_token *newargtkn)
{
	char	**new;
	int		i;

	new = (char **)(malloc(sizeof(char *) * ((cmd->argc) + 2)));
	i = 0;
	while (i < cmd->argc)
	{
		new[i] = cmd->argv[i];
		i++;
	}
	new[i] = newargtkn->cnt;
	new[i + 1] = NULL;
	ft_lstadd_back(&cmd->arglst, ft_lstnew(newargtkn));
	free(cmd->argv);
	cmd->argv = new;
	cmd->argc++;
}

t_command	*new_command(int max_args)
{
	t_command	*cmd;
	int			i;

	cmd = (t_command *)malloc(sizeof(t_command));
	cmd->argc = 0;
	cmd->argv = (char **)(malloc(sizeof(char *) * 2));
	cmd->argv[0] = NULL;
	cmd->argv[1] = NULL;
	cmd->is_assignment = 0;
	cmd->name = NULL;
	cmd->filein = NULL;
	cmd->lastfileout = NULL;
	cmd->fileouts = NULL;
	cmd->fileoutc = 0;
	cmd->hdocword = NULL;
	cmd->argc = 0;
	cmd->append = 0;
	cmd->piped = 0;
	cmd->fileintkn = NULL;
	cmd->arglst = NULL;
	cmd->hdoctkn = NULL;
	cmd->lastfileouttkn = NULL;
	return (cmd);
}

/* Adds file path to fileouts list.
Makes a new fileouts list if it didn't exist. */
void	add_fileout(t_command *cmd, t_token *file, int operator)
{
	t_fileout	*fo;
	int			i;

	fo = (t_fileout *)malloc(sizeof(t_fileout));
	fo->file = file->cnt;
	fo->filetkn = file;
	fo->append = 0;
	if (operator == OT_ORED2)
		fo->append = 1;
	if (cmd->fileouts == NULL)
		cmd->fileouts = ft_lstnew(fo);
	else
		ft_lstadd_back(&cmd->fileouts, ft_lstnew(fo));
	cmd->fileoutc++;
	cmd->lastfileout = file->cnt;
	cmd->lastfileouttkn = file;
}
