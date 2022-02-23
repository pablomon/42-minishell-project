/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:09:01 by pmontese          #+#    #+#             */
/*   Updated: 2022/02/23 13:30:13 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"
#define DEBUG 0

int	delim_op_rules(t_tokenizer *d, t_token *token, char *str)
{
	if (DEBUG)
		printf("OPERATOR RULES\n");
/* If the previous character was used as part of an operator and the current character is not quoted
and can be used with the current characters to form an operator,
it shall be used as part of that (operator) token. */
	if (!d->quoted && token->type == TT_OP)
	{
		if (DEBUG)
			printf("Checking size 2 operator\n");
		if ((d->c == '<' && d->prev == '<')
			|| (d->c == '>' && d->prev == '>'))
		{
			if (DEBUG)
				printf("Adding character to operator\n");
			d->cnt = ft_strjoinchar(d->cnt, d->c);
			d->prev = d->c;
			d->spos++;
			d->tpos++;
			// HERE DOCUMENT
			if (d->c == '<' && d->prev == '<')
				d->heredoc = 1;
		}
/* If the previous character was used as part of an operator
and the current character cannot be used with the current characters to form an operator,
the operator containing the previous character shall be delimited.*/
		return (delimit_tkn(d, token));
	}
	return(0);
}
int quote_rules(t_tokenizer *d, t_token *token, char *str)
{
		if (DEBUG)
			printf("QUOTATION RULES\n");
	/* If the current character is backslash, single-quote, or double-quote ( '\', '", or ' )' and it is not quoted,
it shall affect quoting for subsequent characters up to the end of the quoted text.
The rules for quoting are as described in Quoting.
During token recognition no substitutions shall be actually performed,
and the result token shall contain exactly the characters that appear in the input (except for <newline> joining),
unmodified, including any embedded or enclosing quotes or substitution operators,
between the quote mark and the end of the quoted text.
The token shall not be delimited by the end of the quoted field. */
	if (!d->quoted && (d->c == '\'' || d->c == '"'))
	{
		if (d->c == '\'')
		{
			if (DEBUG)
				printf("Single Quoting\n");
			d->quoted = SQUOTE;
			token->quoted = SQUOTE;
		}
		else
		{
			if (DEBUG)
				printf("Double Quoting\n");
			d->quoted = DQUOTE;
			token->quoted = DQUOTE;
		}
		d->spos++;
		return (SKIP);
	}
	if ((d->quoted == SQUOTE && d->c == '\'') || (d->quoted == DQUOTE && d->c == '"'))
	{
		if (DEBUG)
			printf("Closing quote\n");
		d->quoted = 0;
		d->spos++;
		return (SKIP);
	}
	return (0);
}
int	mark_exp_rules(t_tokenizer *d, t_token *token, char *str)
{
	if (DEBUG)
		printf("EXPANSION RULES\n");
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

	if (d->quoted!=SQUOTE && d->c == '$' &&\
	((str[d->spos + 1]) == '?' || isvalidchar4var((str[d->spos + 1]), 1)))
	{
		if (!token->expandable)
		{
			if (DEBUG)
				printf("Found $+? or var. Marked as expandable\n");
			token->expandable = 1;
			return (SKIP);
		}
	}
	return (0);
}
int	newop_rules(t_tokenizer *d, t_token *token, char *str)
{
	if (DEBUG)
		printf("NEW OPERATOR RULES\n");
/* If the current character is not quoted and can be used as the first character of a new operator,
the current token (if any) shall be delimited.
The current character shall be used as the beginning of the next (operator) token. */
	if (!d->quoted && is_op(d->c))
	{
		if (token->type != TT_EMPTY)
		{
			return (delimit_tkn(d, token));
			if (DEBUG)
				printf("Delimit token\n");
		}
		if (DEBUG)
			printf("Starting operator\n");
		token->type = TT_OP;
		// d->cnt[0] = d->c;
		d->cnt = ft_strjoinchar(d->cnt, d->c);
		d->prev = d->c;
		d->spos++;
		d->tpos++;
		return (SKIP);
	}
	return (0);
}
int word_rules(t_tokenizer *d, t_token *token, char *str)
{
	if (DEBUG)
		printf("WORD RULES\n");
// If the current character is an unquoted <newline>, the current token shall be delimited.
	if (!d->quoted && d->c == '\n')
	{
		if (token->type != TT_EMPTY)
		{
			return (delimit_tkn(d, token));
		}
		return(SKIP);
	}
/* If the current character is an unquoted <blank>, any token containing the previous character is delimited
and the current character shall be discarded. */
	if (!d->quoted && (d->c == ' ' || d->c == '\t'))
	{
		if (DEBUG)
			printf("Found blank\n");
		d->spos++;
		if (token->type != TT_EMPTY)
			return (delimit_tkn(d, token));
		return(SKIP);
	}

// If the previous character was part of a word, the current character shall be appended to that word.
	if (token->type == TT_WORD)
	{
		if (DEBUG)
			printf("%c\n", d->c);
		d->cnt = ft_strjoinchar(d->cnt, d->c);
		d->tpos++;
		d->spos++;
		return(SKIP);
	}
// The current character is used as the start of a new word.
	if (DEBUG)
		printf("Starting word: \n%c\n", d->c);
	token->type = TT_WORD;
	// d->cnt[0] = d->c;
	d->cnt = ft_strjoinchar(d->cnt, d->c);
	d->spos++;
	d->tpos++;
	return (0);
}
