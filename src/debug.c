#include "../inc/myshell.h"

void	print_tkn(t_token *tkn)
{
	if (tkn->type == TT_WORD)
	{
		printf("type = word, ");
		printf("expandable = %d, ", tkn->expandable);
		printf("content = %s\n", tkn->cnt);
	}
	if (tkn->type == TT_OP)
	{
		printf("type = operator, ");
		printf("content = %s\n", tkn->cnt);
	}
	if (tkn->type == TT_EMPTY)
		printf("type = empty\n");
	if (tkn->type == TT_EOF)
		printf("type = EOF\n");
}

void	print_cmd(t_command *cmd)
{
	int		i;
	t_token	*t;
	t_list	*lst;

	t = (t_token*)(cmd->arglst->content);
	ft_putstr("name ");
	ft_putendl_fd(t->cnt, 1);
	printf("argc	= %d\n" ,cmd->argc);
	lst = cmd->arglst;
	i = 0;
	printf("args en tokens:\n");
	while (lst)
	{
		ft_putstr("argv[");
		ft_putnbr_fd(i, 1);
		ft_putstr("]	= ");
		if (lst->content == NULL)
			break;
		t = (t_token*)(lst->content);
		printf("'%s'\n" , t->cnt);
		lst = lst->next;
		i++;
	}
	i = 0;
	printf("args en array:\n");
	while (cmd->argv[i])
	{
		printf("argv[%d] = '%s'\n", i, cmd->argv[i]);
		i++;
	}
	if (cmd->fileintkn)
		printf("in	= '%s'\n", cmd->fileintkn->cnt);
	printf("append	= %d\n", cmd->append);
	printf("fileoutc	= %d\n", cmd->fileoutc);
	lst = cmd->fileouts;
	i = 0;
	while (i < cmd->fileoutc)
	{
		t_fileout *cnt;
		cnt = (t_fileout*)lst->content;
		printf("fileout[%d]	= \"'%s'\", append = %d\n", i, cnt->filetkn->cnt, cnt->append);
		if (lst->next)
			lst = lst->next;
		i++;
	}
	if (cmd->lastfileouttkn)
		printf("out	= '%s'\n", cmd->lastfileouttkn->cnt);
	if (cmd->hdocword)
		printf("heredoc word	= '%s'\n", cmd->hdoctkn->cnt);
	printf("is piped = %d\n", cmd->piped);
	printf("\n");
}

void	print_arr(char **arr)
{
	printf("print_arr:\n");
	int i;

	i = 0;
	while (arr[i])
	{
		printf("arr[%d] = '%s'\n", i , arr[i]);
		i++;
	}
}
