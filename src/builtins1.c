/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:01:06 by pmontese          #+#    #+#             */
/*   Updated: 2022/02/25 01:00:29 by pmontese         ###   ########.fr       */
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
	t_list	*arglst;
	t_list	*reslst;
	t_token	*t;
	char	*str;
	char	*tmp;

	reslst = NULL;
	str = ft_strdup("");
	arglst = cmd->arglst->next;
	while (arglst)
	{
		t = (t_token *)arglst->content;
		tmp = str;
		str = ft_strjoin(str, t->cnt);
		free(tmp);
		if (t->spaced || arglst->next == NULL)
		{
			ft_lstadd_back(&reslst, ft_lstnew(str));
			str = ft_strdup("");
		}
		arglst = arglst->next;
	}
	free(str);
	return (reslst);
}

int	bi_export_check(t_command *cmd, t_param *param, int is_child)
{
	if (cmd->argc == 1)
	{
		if (is_child)
			print_export(param);
		return (1);
	}
	if (is_child)
		return (1);
	return (0);
}

void	bi_export(t_command *cmd, t_param *param, int is_child)
{
	char	*arg;
	t_list	*joinedlst;
	t_list	*lst;

	g_status = 0;
	if (bi_export_check(cmd, param, is_child))
		return ;
	joinedlst = export_join_args(cmd);
	lst = joinedlst;
	while (lst)
	{
		arg = (char *)lst->content;
		if (!is_valid_identifier(arg, 1))
		{
			my_perror(WRONGID, arg, 1);
			lst = lst->next;
			continue ;
		}
		set_env_var(get_keyval(arg), param);
		lst = lst->next;
	}
	ft_lstclear(&joinedlst, freefunc);
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
