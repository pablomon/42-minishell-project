/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 22:27:03 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/23 22:48:59 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

void	free_tokens(t_list *tknlst)
{
	t_token	*t;
	t_list	*tmp;

	if (!tknlst)
		return ;
	tmp = tknlst;
	while (tmp)
	{
		t = (t_token *)(tmp->content);
		if (t->type != TT_EOF)
			free(t->cnt);
		free(t);
		tmp = tmp->next;
	}
	ft_lstclear(&tknlst, emptyfunc);
}

void	free_commands(t_list *cmd_lst)
{
	t_command	*cmd;
	t_list		*tmp;
	t_list		*tmp2;

	tmp = cmd_lst;
	while (tmp)
	{
		cmd = tmp->content;
		ft_lstclear(&cmd->arglst, emptyfunc);
		free(cmd->arglst);
		tmp2 = cmd->fileouts;
		while (tmp2)
		{
			free(tmp2->content);
			tmp2 = tmp2->next;
		}
		if (cmd->fileouts)
			ft_lstclear(&cmd->fileouts, emptyfunc);
		free(cmd->fileouts);
		free(cmd->argv);
		free(cmd);
		tmp = tmp->next;
	}
	ft_lstclear(&cmd_lst, emptyfunc);
}

void	cleanup(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->envc)
	{
		free(param->env[i]->key);
		free(param->env[i]->val);
		free(param->env[i]);
		i++;
	}
	free(param->env);
	free_tokens(param->tkn_lst);
	if (param->cmd_lst)
		free_commands(param->cmd_lst);
	free(param->prompt);
	free(param->line);
	free(param);
}
