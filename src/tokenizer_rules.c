/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:09:01 by pmontese          #+#    #+#             */
/*   Updated: 2022/02/24 00:20:07 by pmontese         ###   ########.fr       */
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

int	quote_rules(t_tokenizer *d, t_token *token, char *str)
{
	char	c;
	if (!d->quoted && (d->c == '\'' || d->c == '"'))
	{
		if (DEBUG)
			ft_putendl_fd("quotes", 1);
		if (d->c == '\'')
		{
			if (str[d->spos + 1] == '\'')
			{
				d->spos += 2;
				return (SKIP);
			}
			d->quoted = SQUOTE;
		}
		else
		{
			if (str[d->spos + 1] == '"')
			{
				d->spos += 2;
				return (SKIP);
			}
			d->quoted = DQUOTE;
		}
		d->spos++;
		if (token->type != TT_EMPTY && str[d->spos])
			return (delimit_tkn(d, token));
		return (SKIP);
	}
	if ((d->quoted == SQUOTE && d->c == '\'') \
	|| (d->quoted == DQUOTE && d->c == '"'))
	{
		if (DEBUG)
			ft_putendl_fd("close quotes", 1);
		d->quoted = 0;
		d->spos++;
		c = str[d->spos];
		if (token->type == TT_EMPTY)
		{
			return (SKIP);
		}
		if (c == ' ' || c == '\t')
			token->spaced = 1;
		if (DEBUG)
		{
			printf("c = '%c', ", str[d->spos]);
			printf("spaced = %d\n", token->spaced);
			printf("spos = %d\n", d->spos);
		}
		return (delimit_tkn(d, token));
	}
	return (0);
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

int	word_rules(t_tokenizer *d, t_token *token, char *str)
{
	if (!d->quoted && d->c == '\n')
	{
		if (token->type != TT_EMPTY)
			return (delimit_tkn(d, token));
		return (SKIP);
	}
	if (!d->quoted && (d->c == ' ' || d->c == '\t'))
	{
		if (DEBUG)
			printf("found blank\n");
		d->spos++;
		token->spaced = 1;
		if (token->type != TT_EMPTY)
			return (delimit_tkn(d, token));
		return (SKIP);
	}
	if (token->type == TT_WORD)
	{
		d->cnt = ft_strjoinchar(d->cnt, d->c);
		d->tpos++;
		d->spos++;
		return (SKIP);
	}
	token->type = TT_WORD;
	token->quoted = d->quoted;
	d->cnt = ft_strjoinchar(d->cnt, d->c);
	d->spos++;
	d->tpos++;
	return (0);
}
