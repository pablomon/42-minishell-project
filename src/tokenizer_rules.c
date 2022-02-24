/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:09:01 by pmontese          #+#    #+#             */
/*   Updated: 2022/02/24 01:11:40 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"
#define DEBUG 0

int	delim_op_rules(t_tokenizer *d, t_token *token, char *str)
{
	if (!d->quoted && token->type == TT_OP)
	{
		if ((d->c == '<' && d->prev == '<')
			|| (d->c == '>' && d->prev == '>'))
		{
			d->cnt = ft_strjoinchar(d->cnt, d->c);
			d->prev = d->c;
			d->spos++;
			d->tpos++;
			if (d->c == '<' && d->prev == '<')
				d->heredoc = 1;
		}
		return (delimit_tkn(d, token));
	}
	return (0);
}

int	quote_rules2(t_tokenizer *d, t_token *token, char *str)
{
	if ((d->quoted == SQUOTE && d->c == '\'') \
	|| (d->quoted == DQUOTE && d->c == '"'))
	{
		d->quoted = 0;
		d->spos++;
		if (token->type == TT_EMPTY)
			return (SKIP);
		if (str[d->spos] == ' ' || str[d->spos] == '\t')
			token->spaced = 1;
		return (delimit_tkn(d, token));
	}
	return (0);
}

int	quote_rules(t_tokenizer *d, t_token *token, char *str)
{
	if (!d->quoted && (d->c == '\'' || d->c == '"'))
	{
		if (str[d->spos + 1] == d->c)
		{
			d->spos += 2;
			return (SKIP);
		}
		d->quoted = SQUOTE;
		if (d->c == '"')
			d->quoted = DQUOTE;
		d->spos++;
		if (token->type != TT_EMPTY && str[d->spos])
			return (delimit_tkn(d, token));
		return (SKIP);
	}
	return (quote_rules2(d, token, str));
}

int	mark_exp_rules(t_tokenizer *d, t_token *token, char *str)
{
	if (d->quoted != SQUOTE && d->c == '$' && \
	((str[d->spos + 1]) == '?' || isvalidchar4var((str[d->spos + 1]), 1)))
	{
		if (!token->expandable)
		{
			token->expandable = 1;
			return (SKIP);
		}
	}
	return (0);
}

int	newop_rules(t_tokenizer *d, t_token *token, char *str)
{
	if (!d->quoted && is_op(d->c))
	{
		if (token->type != TT_EMPTY)
		{
			return (delimit_tkn(d, token));
		}
		token->type = TT_OP;
		d->cnt = ft_strjoinchar(d->cnt, d->c);
		d->prev = d->c;
		d->spos++;
		d->tpos++;
		return (SKIP);
	}
	return (0);
}
