#include "../inc/myshell.h"
#define DEBUG 0

int	is_op(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '\n')
		return (1);
	return (0);
}

int	delimit_tkn(t_tokenizer *d, t_token *tkn)
{
	if (DEBUG)
		printf("Delimiting token\n");
	tkn->cnt = d->cnt;
	// tkn->cnt[d->tpos] = 0;
	if (tkn->type != TT_OP)
		return (1);
	if (tkn->cnt[0] == '>')
		tkn->op_type = OT_ORED;
	if (tkn->cnt[0] == '<')
		tkn->op_type = OT_IRED;
	if (tkn->cnt[0] == '>' && tkn->cnt[1] == '>')
		tkn->op_type = OT_ORED2;
	if (tkn->cnt[0] == '<' && tkn->cnt[1] == '<')
		tkn->op_type = OT_HEREDOC;
	if (tkn->cnt[0] == '|')
		tkn->op_type = OT_PIPE;
	if (tkn->cnt[0] == '\n')
		tkn->op_type = OT_NEWLINE;
	return (1);
}

int	put_token(char *str, t_token *token, t_param *param)
{
	static t_tokenizer	d;
	static int			heredoc = 0;
	static int			pos = 0;

	init_tokenizer_struct(&d, heredoc, pos, str);
	tokenize(&d, token, param);
	// Update static vars
	pos = d.spos;
	heredoc = d.heredoc;
	// If the end of input is recognized, the current token shall be delimited. If there is no current token, the end-of-input indicator shall be returned as the token.
	if (token->type == TT_EMPTY)
	{
		token->type = TT_EOF;
		if (DEBUG)
			printf("No more content, returning EOF\n");
		//reset static var
		heredoc = 0;
		pos = 0;
		free(d.cnt);
		return (0);
	}
	else
	{
		delimit_tkn(&d, token);
		// save state
		heredoc = d.heredoc;
		pos = d.spos;
		return (1);
	}
}

t_token *new_token()
{
	t_token	*t;

	t = (t_token *)malloc(sizeof(t_token));
	t->delimited = 0;
	t->type = TT_EMPTY;
	t->op_type = 0;
	t->expandable = 0;

	return (t);
}

t_list	*get_tokens(char *input, t_param *param)
{
	if (DEBUG)
		printf("---- LEXER ----\n");
	t_token *tokens;
	int i;

	t_list	*tkn_lst;
	t_list	*tmp;
	t_token	*t;

	tkn_lst = ft_lstnew(new_token());
	tmp = tkn_lst;
	while (put_token(input, tmp->content, param))
	{
		if (DEBUG)
		{
			t = (t_token*)(tmp->content);
			if (t->type != TT_EOF)
				printf("token : '%s'\n", t->cnt);
		}
		ft_lstadd_back(&tkn_lst, ft_lstnew(new_token()));
		tmp = tmp->next;
	}
	if (DEBUG)
	{
		printf("\nShowing obtained tokens..\n");
		tmp = tkn_lst;
		i = 0;
		while (tmp)
		{
			t = (t_token*)(tmp->content);
			printf("Token %d: ", i);
			print_tkn(t);
			if (t->type == TT_EOF)
				break;
			tmp = tmp->next;
			i++;
		}
	}

	return tkn_lst;
}