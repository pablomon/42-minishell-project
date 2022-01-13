#include "../inc/myshell.h"
#define MAX_TKNS 1000

int	is_op(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '\n')
		return (1);
	return (0);
}

int	delimit_tkn(int tkn_pos, char *cnt, t_token *tkn)
{
	printf("returning delimited token\n");
	cnt[tkn_pos] = 0;
	tkn->cnt = ft_strdup(cnt);
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
	return (1);
}

int	get_token(char **str, int *pos, t_token *token)
{
	ft_putstr("\nObteniendo token...\n");

	char		prev;
	int			quoted;
	int			tkn_pos;
	char		cnt[1000]; // change to str append
	char		c;

	prev = '\0';
	quoted = NOQUOTE;
	tkn_pos = 0;

	printf("source: %s\n", &((*str)[*pos]));
	while (((*str)[*pos]) != 0) // TODO cambiar por EOF ???
	{
		c = ((*str)[*pos]);
		if (token->delimited)
		{
			printf("returning delimited token\n");
			cnt[tkn_pos] = 0;
			token->cnt = ft_strdup(cnt);
			return (1);
		}
/* If the previous character was used as part of an operator and the current character is not quoted
and can be used with the current characters to form an operator,
it shall be used as part of that (operator) token. */
		if (!quoted && token->type == TT_OP)
		{
			printf("Checking size 2 operator\n");
			if ((c == '<' && prev == '<')
				|| (c == '>' && prev == '>'))
			{
				printf("Adding character to operator\n");
				cnt[tkn_pos] = c;
				prev = c;
				*pos = *pos + 1;
				tkn_pos++;
			}
/* If the previous character was used as part of an operator
and the current character cannot be used with the current characters to form an operator,
the operator containing the previous character shall be delimited.*/
			return (delimit_tkn(tkn_pos, cnt, token));
			printf("..");
			continue;
		}
/* If the current character is backslash, single-quote, or double-quote ( '\', '", or ' )' and it is not quoted,
it shall affect quoting for subsequent characters up to the end of the quoted text.
The rules for quoting are as described in Quoting.
During token recognition no substitutions shall be actually performed,
and the result token shall contain exactly the characters that appear in the input (except for <newline> joining),
unmodified, including any embedded or enclosing quotes or substitution operators,
between the quote mark and the end of the quoted text.
The token shall not be delimited by the end of the quoted field. */
		if (!quoted && (c == '\'' || c == '"'))
		{
			if (c == '\'')
			{
				printf("Single Quoting\n");
				quoted = SQUOTE;
			}
			else
			{
				printf("Double Quoting\n");
				quoted = DQUOTE;
			}
			*pos = *pos + 1;
			continue;
		}
		if ((quoted == SQUOTE && c == '\'') || (quoted == DQUOTE && c == '"'))
		{
			printf("Closing quote\n");
			quoted = 0;
			*pos = *pos + 1;
			continue;
		}
/* If the current character is an unquoted '$' or '`',
the shell shall identify the start of any candidates for parameter expansion ( Parameter Expansion),
command substitution ( Command Substitution), or arithmetic expansion ( Arithmetic Expansion)
from their introductory unquoted character sequences:
'$' or "${", "$(" or '`', and "$((", respectively.
The shell shall read sufficient input to determine the end of the unit to be expanded (as explained in the cited sections).
While processing the characters, if instances of expansions or quoting are found nested within the substitution,
the shell shall recursively process them in the manner specified for the construct that is found.
The characters found from the beginning of the substitution to its end, allowing for any recursion necessary to recognize embedded constructs,
shall be included unmodified in the result token, including any embedded or enclosing substitution operators or quotes.
The token shall not be delimited by the end of the substitution.*/
		if (quoted!=SQUOTE && c == '$')
		{
				printf("Call expander:\n");
				int exp_res = expander(str, *pos);
				if (exp_res == -1)
				{
					*pos = *pos + 1;
				}
				if (exp_res == 0)
				{
					continue;
				}
				*pos = *pos + exp_res;
		}
/* If the current character is not quoted and can be used as the first character of a new operator,
the current token (if any) shall be delimited.
The current character shall be used as the beginning of the next (operator) token. */
		if (!quoted && is_op(c))
		{
			if (token->type != TT_EMPTY)
			{
				return (delimit_tkn(tkn_pos, cnt, token));
				continue;
			}
			printf("Starting operator\n");
			token->type = TT_OP;
			cnt[0] = c;
			prev = c;
			*pos = *pos + 1;
			tkn_pos++;
			continue;
		}
// If the current character is an unquoted <newline>, the current token shall be delimited.
		if (!quoted && c == '\n')
		{
			// *pos = *pos + 1;
			if (token->type != TT_EMPTY)
				return (delimit_tkn(tkn_pos, cnt, token));
			continue;
		}
/* If the current character is an unquoted <blank>, any token containing the previous character is delimited
and the current character shall be discarded. */
		if (!quoted && (c == ' ' || c == '\t'))
		{
			printf("Found blank\n");
			*pos = *pos + 1;
			if (token->type != TT_EMPTY)
				return (delimit_tkn(tkn_pos, cnt, token));
			continue;
		}

// If the previous character was part of a word, the current character shall be appended to that word.
		if (token->type == TT_WORD)
		{
			printf("%c\n", c);
			cnt[tkn_pos] = c;
			tkn_pos++;
			*pos = *pos + 1;
			continue;
		}

/* If the current character is a '#', it and all subsequent characters up to, but excluding,
the next <newline> shall be discarded as a comment.
The <newline> that ends the line is not considered part of the comment. */
		// Creo que no hay que hacerlo

// The current character is used as the start of a new word.
		printf("Starting word: \n%c\n", c);
		token->type = TT_WORD;
		cnt[0] = c;
		*pos = *pos + 1;
		tkn_pos++;
	}
	// If the end of input is recognized, the current token shall be delimited. If there is no current token, the end-of-input indicator shall be returned as the token.
	if (token->type == TT_EMPTY)
	{
		token->type = TT_EOF;
		printf("No content, returning EOF\n");
		return (0);
	}
	delimit_tkn(tkn_pos, cnt, token);
	return (1);
}

t_token	*tokenizer(char *input)
{
	printf("---- LEXER ----\n");
	t_token *tokens;
	int i;
	int pos;

	tokens = (t_token *)malloc(MAX_TKNS * sizeof(t_token));
	i = 0;
	while (i < MAX_TKNS)
	{
		tokens[i].delimited = 0;
		tokens[i].type = TT_EMPTY;
		tokens[i].op_type = 0;
		i++;
	}
	pos = 0;
	i = 0;
	while (get_token(&input, &pos, &tokens[i]))
	{
		printf("token : '%s'\n", tokens[i].cnt);
		i++;
	}
	i = 0;
	printf("\nShowing obtained tokens..");
	while (1)
	{
		printf("token %d: '%s'\n", i, tokens[i].cnt);
		if (tokens[i].type == TT_EOF)
			break;
		i++;
	}
	return tokens;
}
