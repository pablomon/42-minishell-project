/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:55:41 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/23 19:00:03 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

/**
 * * Disables CTRL hotkey(+c) from printing ^C
*/
static void	disable_ctrl_c_hotkey(void)
{
	struct termios	termios;
	int				rc;

	rc = tcgetattr(0, &termios);
	if (rc)
	{
		perror("tcgetattr");
		exit (1);
	}
	termios.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &termios);
	if (rc)
	{
		perror("tcsetattr");
		exit (1);
	}
}

void	increment_shlvl(t_param *param)
{
	int		ilvl;
	char	*slvl;

	slvl = mygetenv("SHLVL", param);
	if (slvl)
	{
		ilvl = ft_atoi(slvl);
		slvl = ft_itoa(ilvl + 1);
		my_setenv("SHLVL", slvl, param);
		free (slvl);
	}
	else
		my_setenv("SHLVL", "1", param);
}

void	update_prompt(t_param *param)
{
	char		*logname;
	char		*pwd;
	char		*tmp;

	if (mygetenv("LOGNAME", param))
	{
		logname = ft_strdup(mygetenv("LOGNAME", param));
		tmp = logname;
		logname = ft_strjoin(logname, ":");
		free (tmp);
	}
	else
		logname = ft_strdup("");
	if (mygetenv("PWD", param))
		pwd = ft_strdup(mygetenv("PWD", param));
	else
		pwd = ft_strdup("");
	tmp = ft_strjoin(logname, pwd);
	free (pwd);
	free (param->prompt);
	param->prompt = ft_strjoin(tmp, "$ ");
	free (tmp);
	free (logname);
}

int	main(int ac, char *av[], char **env)
{
	t_param	*param;
	int		status;
	char	*strlvl;
	int		intlvl;

	status = 0;
	param = (t_param *)malloc(sizeof(t_param));
	init_param(param, env, getcwd(NULL, 0));
	increment_shlvl(param);
	disable_ctrl_c_hotkey();
	reg_parent_signals();
	update_prompt(param);
	printf("\n%s\n", "M I N I S H E L L\t\t\tby pmontese & lvintila\n");
	status = myshell_loop(param, av);
	cleanup(param);
	return (status);
}
