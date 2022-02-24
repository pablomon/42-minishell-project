/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_rules2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 01:09:59 by pmontese          #+#    #+#             */
/*   Updated: 2022/02/24 01:10:38 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

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
		d->spos++;
		token->spaced = 1;
		if (token->type != TT_EMPTY)
			return (delimit_tkn(d, token));
		return (SKIP);
	}
	d->tpos++;
	d->spos++;
	if (token->type == TT_WORD)
	{
		d->cnt = ft_strjoinchar(d->cnt, d->c);
		return (SKIP);
	}
	token->type = TT_WORD;
	token->quoted = d->quoted;
	d->cnt = ft_strjoinchar(d->cnt, d->c);
	return (0);
}
