/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:09:24 by pmontese          #+#    #+#             */
/*   Updated: 2022/02/23 19:44:21 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"
#define DEBUG 0

void	init_tokenizer_struct(t_tokenizer *d, int heredoc, int pos, char *str)
{
	d->cnt = NULL;
	d->prev = 0;
	d->quoted = NOQUOTE;
	d->tpos = 0;
	d->spos = pos;
	d->heredoc = heredoc;
	d->str = str;
}

/* Implements token rules */
int	token_rules(t_tokenizer *data, t_token *token, char *str)
{
	int	res;

	res = 0;
	if (delim_op_rules(data, token, str) == RET)
		return (1);
	if (quote_rules(data, token, str) == SKIP)
		return (0);
	if (mark_exp_rules(data, token, str) == SKIP)
		return (0);
	res = newop_rules(data, token, str);
	if (res == RET)
		return (1);
	if (res == SKIP)
		return (0);
	if (word_rules(data, token, str) == RET)
		return (1);
	return (0);
}

void	tokenize(t_tokenizer *d, t_token *token, t_param *param)
{
	while (d->str[d->spos] != 0)
	{
		if (d->heredoc)
		{
			token->type = TT_WORD;
			free(d->cnt);
			d->cnt = read_heredoc(d->str, d, token);
			d->heredoc = 0;
			return ;
		}
		if (token->delimited)
		{
			token->cnt = d->cnt;
			return ;
		}
		d->c = d->str[d->spos];
		d->ruleres = token_rules(d, token, d->str);
		if (d->ruleres == 1)
			return ;
	}
}
