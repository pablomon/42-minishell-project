/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 23:19:44 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/23 23:21:20 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

void	parent_hdl(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	ft_putstr("\n");
	rl_redisplay();
}

void	child_hdl(int signum)
{
	if (signum == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 2);
}

void	reg_parent_signals(void)
{
	signal(SIGINT, parent_hdl);
	signal(SIGQUIT, SIG_IGN);
}

void	reg_child_signals(void)
{
	signal(SIGINT, child_hdl);
	signal(SIGQUIT, child_hdl);
}
