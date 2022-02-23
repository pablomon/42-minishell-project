/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:01:06 by pmontese          #+#    #+#             */
/*   Updated: 2022/02/23 21:53:06 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

static int	is_n_opt(t_list *arglst, int i, int skip)
{
	t_token	*t;
	char	*argv;

	while (arglst && arglst->content)
	{
		t = (t_token *) arglst->content;
		argv = t->cnt;
		if (argv && ft_strlen(argv) > 0)
		{
			if (argv && argv[0] == '-' && argv[1] == 'n')
			{
				argv++;
				while (*argv == 'n')
					argv++;
				if (argv && *argv == '\0')
				{
					i++;
					arglst = arglst->next;
					continue ;
				}
			}
		}
		break ;
	}
	return (i);
}

/* remove spaces extern spaces */
char	*trim_str(t_token *t)
{
	int		i;
	int		lft;
	int		rgt;
	char	*new;
	int		quote;

	if (t->quoted != 0)
		return (ft_strdup(t->cnt));
	new = ft_strdup("");
	lft = 0;
	while (ft_isspace(t->cnt[lft]))
		lft++;
	rgt = ft_strlen(t->cnt) - 1;
	while (ft_isspace(t->cnt[rgt]))
		rgt--;
	i = lft;
	while (i <= rgt)
	{
		new = ft_strjoinchar(new, t->cnt[i]);
		i++;
	}
	return (new);
}

char	*do_echo(t_list	*lst)
{
	char	*out;
	char	*tmp;
	char	*trimmed;
	t_token	*t;
	t_token	*t1;

	out = ft_strdup("");
	while (lst)
	{
		t = (t_token *)lst->content;
		trimmed = trim_str(t);
		tmp = out;
		out = ft_strjoin(out, trimmed);
		free(trimmed);
		free(tmp);
		if (lst->next)
		{
			t1 = (t_token *)lst->next->content;
			if (t1->cnt && ft_strlen(t1->cnt) != 0 && t->spaced)
				out = ft_strjoinchar(out, ' ');
		}
		lst = lst->next;
	}
	return (out);
}

int	bi_echo(t_command *cmd, int ischild)
{
	int		i;
	char	*out;
	t_list	*lst;
	int		skipn;

	g_status = 0;
	if (!ischild)
		return (0);
	lst = cmd->arglst->next;
	skipn = is_n_opt(cmd->arglst->next, 0, 0);
	lst = ft_lstat(cmd->arglst->next, skipn);
	out = do_echo(lst);
	ft_putstr_fd(out, 1);
	if (skipn <= 0)
		ft_putchar_fd('\n', 1);
	free(out);
	return (0);
}
