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
	printf("name	= %s\n" ,t->cnt);
	printf("argc	= %d\n" ,cmd->argc);
	lst = cmd->arglst;
	i = 0;
	while (lst)
	{
		ft_putstr("argv[");
		ft_putnbr_fd(i, 1);
		ft_putstr("]	= ");
		if (lst->content == NULL)
			break;
		t = (t_token*)(lst->content);
		printf("%s\n" , t->cnt);
		lst = lst->next;
		i++;
	}
	if (cmd->fileintkn)
		printf("in	= %s\n", cmd->fileintkn->cnt);
	printf("append	= %d\n", cmd->append);
	printf("fileoutc	= %d\n", cmd->fileoutc);
	lst = cmd->fileouts;
	i = 0;
	while (i < cmd->fileoutc)
	{
		t_fileout *cnt;
		cnt = (t_fileout*)lst->content;
		printf("fileout[%d]	= \"%s\", append = %d\n", i, cnt->filetkn->cnt, cnt->append);
		if (lst->next)
			lst = lst->next;
		i++;
	}
	if (cmd->lastfileouttkn)
		printf("out	= %s\n", cmd->lastfileouttkn->cnt);
	if (cmd->hdocword)
		printf("heredoc word	= %s\n", cmd->hdoctkn->cnt);
	printf("is piped = %d\n", cmd->piped);
	printf("\n");
}

void	print_cmd2(t_command *cmd)
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
	printf("append	= %d\n", cmd->append);
	printf("fileoutc	= %d\n", cmd->fileoutc);
	t_list *lst;
	lst = cmd->fileouts;
	i = 0;
	while (i < cmd->fileoutc)
	{
		t_fileout *cnt;
		cnt = (t_fileout*)lst->content;
		printf("fileout[%d]	= \"%s\", append = %d\n", i, cnt->file, cnt->append);
		if (lst->next)
			lst = lst->next;
		i++;
	}
	printf("out	= %s\n", cmd->lastfileout);
	printf("heredoc word	= %s\n", cmd->hdocword);
	printf("is piped = %d\n", cmd->piped);
	printf("\n");
}

void	print_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		ft_putstr(arr[i]);
		i++;
	}
}