/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:14:04 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/20 17:47:18 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

void	*my_perror(t_param *param, int err_type, char *str, int errnum)
{
	g_status = errnum;
	if (err_type == NOQUOTE)
		ft_putstr_fd("minishell: error while looking for matching quote\n", 2);
	else if (err_type == NODIR)
		ft_putstr_fd("minishell: No such file or directory: ", 2);
	else if (err_type == NOPERM)
		ft_putstr_fd("minishell: permission denied: ", 2);
	else if (err_type == NOCMD)
		ft_putstr_fd("minishell: command not found: ", 2);
	else if (err_type == DUP_ERR)
		ft_putstr_fd("minishell: dup2 failed\n", 2);
	else if (err_type == FORK_ERR)
		ft_putstr_fd("minishell: fork failed\n", 2);
	else if (err_type == PIPE_ERR)
		ft_putstr_fd("minishell: error creating pipe\n", 2);
	else if (err_type == PIPEND_ERR)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (err_type == IS_DIR)
		ft_putstr_fd("minishell: Is a directory: ", 2);
	else if (err_type == NOT_DIR)
		ft_putstr_fd("minishell: Not a directory: ", 2);
	ft_putendl_fd(str, 2);
	return (NULL);
}