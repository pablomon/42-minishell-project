#include "../inc/myshell.h"

void	bi_exit_child(t_command *cmd, t_param *param, int cmd_num)
{
	if (param->cmdc == 1)
		return;
	g_status = 130;
	if (cmd->argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_status = 1;
	}
	else if (cmd->argc == 2)
	{
		g_status = ft_atoi(cmd->argv[1]);
		if (g_status == 0)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			g_status = 255;
		}
	}
}

void	bi_exit_parent(t_command *cmd, t_param *param, int cmd_num)
{
	int		isexit;

	if (cmd_num != 0)
		return;
	isexit = 1;
	g_status = 0;
	if (param->cmdc == 1)
		ft_putendl_fd("exit", 2);
	else
		isexit = 0;
	if (cmd->argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_status = 1;
		isexit = 0;
	}
	else if (cmd->argc == 2)
	{
		g_status = ft_atoi(cmd->argv[1]);
		if (g_status == 0)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			g_status = 255;
		}
	}
	if (isexit)
	{
		cleanup(param);
		exit(g_status);
	}
}

void	bi_env(t_param *param, int is_child)
{
	int i;

	if (!is_child)
		return;
	i = 0;
	while (i < param->envc)
	{
		if (param->env[i]->val)
			printf("%s=%s\n", param->env[i]->key, param->env[i]->val);
		i++;
	}
}

void	bi_unset(t_command *cmd, t_param *param, int ischild)
{
	int		i;
	int		j;
	char	*arg;

	i = 1;
	if (ischild)
		return;
	while (i < cmd->argc && param->cmdc == 1 && !ischild)
	{
		arg = cmd->argv[i];
		//check identifier
		if (!is_valid_identifier(arg, 0))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", arg);
			g_status = 1;
			i++;
			continue;
		}
		j = 0;
		while (j < param->envc)
		{
			if (ft_strcmp(arg, param->env[j]->key) == 0)
			{
				unset_env_var(arg, param);
				break;
			}
			j++;
		}
		i++;
	}
}

void	bi_cd(t_command *cmd, t_param *param, int ischild)
{
	char		*pwd;
	char		*tmp;
	DIR			*dir;
	t_keyval	*kv;

	if (ischild)
		return;
	if (param->cmdc > 1)
		return;
	pwd = getcwd(NULL, 0);
	if (cmd->argc == 1) // if cd sin argumentos
	{
		tmp = mygetenv("HOME", param);
		if (!tmp)
		{
			perror("Error: Home not set");
			g_status = 1;
			return;
		}
	}
	else
		tmp = cmd->argv[1];
	if (access(tmp, F_OK) == -1)
	{
		free(pwd);
		perror("Error: not found");
		g_status = 1;
		return;
	}
	dir = opendir(tmp);
	if (!dir)
	{
		free(pwd);
		perror("Error: not a directory");
		g_status = 1;
		return;
	}
	my_setenv("OLDPWD", pwd, param);
	chdir(tmp);
	free(pwd);
	pwd = getcwd(NULL, 0);
	my_setenv("PWD", pwd, param);
	if (dir)
		closedir(dir);
	free(pwd);
	update_prompt(param);
}
