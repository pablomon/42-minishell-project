/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:55:41 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/21 14:32:50 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

void	init_param(t_param *param, char **env, char *cwd)
{
	int			i;
	t_keyval	*keyval;
	char 		*str;

 	param->line				= NULL;
	param->default_in		= 0;
	param->default_out		= 0;
	param->fd_in			= 0;
	param->fd_out			= 0;
	param->cmdc				= 0;
	param->envc				= 0;
	param->envvalc			= 0;
	param->env				= NULL;
	i = 0;
	while (env[i] != NULL)
	{
		keyval = get_keyval(env[i]);
		set_env_var(keyval, param);
		i++;
	}
	if (!mygetenv("PATH", param))
		my_setenv("PATH", cwd, param);
	free(cwd);
	param->tkn_lst = NULL;
	param->cmd_lst = NULL;
	param->prompt = NULL;
}

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
		exit(1);
	}
	termios.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &termios);
	if (rc)
	{
		perror("tcsetattr");
		exit(1);
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
		free(slvl);
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
		free(tmp);
	}
	else
		logname = ft_strdup("");
	if (mygetenv("PWD", param))
		pwd = ft_strdup(mygetenv("PWD", param));
	else
		pwd = ft_strdup("");
	tmp = ft_strjoin(logname, pwd);
	free(pwd);
	free(param->prompt);
	param->prompt = ft_strjoin(tmp, "$ ");
	free(tmp);
	free(logname);
}

int main(int ac, char *av[], char **env)
{
	t_param *param;
	int execution_coun = 1;
	int status = 0;
	char *strlvl;
	int	intlvl;

	param = (t_param *)malloc(sizeof(t_param));
	init_param(param, env, getcwd(NULL, 0));
	increment_shlvl(param);
	disable_ctrl_c_hotkey();
	reg_parent_signals();
	update_prompt(param);
	
	/* Minishell tester */
	if (ac > 1 && ft_strlen(av[1]) == 2 && av[1][0] == '-' && av[1][1] == 'c')
	{
		int i = 2;
		char *line = av[2];
		char *tmp;
		while (av[++i])
		{
			line = ft_strjoin(line, ft_strdup(" "));
			line = ft_strjoin(line, av[i]);
		}
		param->tkn_lst = get_tokens(line, param);
		param->cmd_lst = parser(param->tkn_lst, param);
		expand_tokens(param->tkn_lst, param);
		cmd_execute(param->cmd_lst, param);
		free_tokens(param->tkn_lst);
		param->tkn_lst = NULL;
		free_commands(param->cmd_lst);
		param->cmd_lst = NULL;
		exit(0);
	}
	printf("\n%s\n", "M I N I S H E L L\t\t\tby pmontese & lvintila\n");

	status = myshell_loop(param, av);
	cleanup(param);
	return (status);
}
