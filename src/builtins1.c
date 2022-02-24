/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:01:06 by pmontese          #+#    #+#             */
/*   Updated: 2022/02/24 20:40:05 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

int	is_valid_identifier(char *arg, int allow_equalsign)
{
	int	i;

	if (isvalidchar4var(arg[0], 1))
	{
		i = 1;
		while (isvalidchar4var(arg[i], 0))
			i++;
		if (allow_equalsign && (arg[i] == '=' || arg[i] == 0))
			return (1);
		if (!allow_equalsign && arg[i] == 0)
			return (1);
	}
	return (0);
}

t_list	*export_join_args(t_command *cmd)
{
	t_list	*lst;
	t_list	*reslst;
	t_token *t;
	char	*str;
	char	*tmp;

	str = ft_strdup("");
	lst = cmd->arglst->next;
	while (lst)
	{
		t = (t_token *)lst->content;
		tmp = str;
		str = ft_strjoin(str, t->cnt);
		free(tmp);
		if (t->spaced || lst->next == NULL)
		{
			ft_lstadd_back(&reslst, ft_lstnew(str));
			str = ft_strdup("");
		}
		lst = lst->next;
	}
	free(str);
	return (reslst);
}

void	free_lst(t_list *lst)
{
	t_list	*tmp;
	t_list	*tmp2;
	char	*str;

	tmp = lst;
	int i = 0;
	while (tmp)
	{
		str = (char *)tmp->content;
		free(str);
		tmp->content = NULL;
		tmp = tmp->next;
	}
	ft_lstclear(&lst, emptyfunc);
}

int	bi_export_check(t_command *cmd, t_param *param, int is_child)
{
	if (cmd->argc == 1 && is_child)
	{
		print_export(param);
		return(1);
	}
	return(0);
}

void	bi_export(t_command *cmd, t_param *param, int is_child)
{
	char	*arg;
	t_list	*joinedlst;
	t_list	*lst;

	g_status = 0;
	if (bi_export_check(cmd, param, is_child))
		return ;
	if (!is_child && param->cmdc == 1)
	{
		joinedlst = export_join_args(cmd);
		lst = joinedlst;
		while (lst)
		{
			arg = (char *)lst->content;
			if (!is_valid_identifier(arg, 1))
			{
				printf("minishell: export: '%s': not a valid identifier\n", arg);
				g_status = 1;
				lst = lst->next;
				continue ;
			}
			set_env_var(get_keyval(arg), param);
			lst = lst->next;
		}
		free_lst(joinedlst);
	}
}

int	bi_pwd(int ischild)
{
	char	*buf;

	if (!ischild)
		return (0);
	buf = getcwd(NULL, 0);
	ft_putstr(buf);
	ft_putstr("\n");
	free(buf);
	return (0);
}
