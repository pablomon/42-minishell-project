/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:14:04 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/25 01:04:48 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

int	my_perror(int err_type, char *str, int errnum)
{
	g_status = errnum;
	if (err_type == WRONGID)
		ft_putstr_fd("minishell: export: not a valid identifier: ", 2);
	if (err_type == NOHOME)
		ft_putstr_fd("minishell: Error: Home not set", 2);
	else if (err_type == NOFILDIR)
		ft_putstr_fd("minishell: No such file or directory: ", 2);
	else if (err_type == NOPERM)
		ft_putstr_fd("minishell: permission denied: ", 2);
	else if (err_type == NOCMD)
		ft_putstr_fd("minishell: command not found: ", 2);
	else if (err_type == DUP_ERR)
		ft_putstr_fd("minishell: dup2 failed", 2);
	else if (err_type == FORK_ERR)
		ft_putstr_fd("minishell: fork failed", 2);
	else if (err_type == PIPE_ERR)
		ft_putstr_fd("minishell: error creating pipe", 2);
	else if (err_type == IS_DIR)
		ft_putstr_fd("minishell: Is a directory: ", 2);
	else if (err_type == NOT_DIR)
		ft_putstr_fd("minishell: Not a directory: ", 2);
	else if (err_type == SYNTAX_ERR)
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putendl_fd(str, 2);
	return (1);
}
