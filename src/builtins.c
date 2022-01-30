#include "../inc/myshell.h"


void	bi_exit(t_command *cmd, t_param *param)
{
	int num;

	// TODO liberar memoria
	printf("exit\n");
	if (cmd->argc > 2)
	{
		printf("bash: exit: too many arguments\n");
		exit(1);
	}
	else if (cmd->argc == 2)
	{
		if (ft_strlen(cmd->argv[1]) == 1 && cmd->argv[1][0] == '0')
			exit(0);
		num = ft_atoi(cmd->argv[1]);
		if (num == 0)
		{
			printf("bash: exit: arg: numeric argument required\n");
			exit(2);
		}		
		exit(num);
	}
	exit(0);
}

void	bi_env(t_param *param)
{
	int i;

	i = 0;
	while (i < param->envc)
	{
		printf("%s=%s\n", param->env[i]->key, param->env[i]->val);
		i++;
	}
}

int is_valid_identifier(char *arg, int equalsign)
{
	int i;

	if (ft_isalpha(arg[0]))
	{
		i = 1;
		while (ft_isalnum(arg[i]))
			i++;
		if (equalsign && arg[i] == '=')
			return (1);
		if (!equalsign && arg[i] == 0)
			return (1);
	}
	return (0);
}

void	bi_export(t_command *cmd, t_param *param)
{
	int i;
	int j;
	char	*arg;

	i = 1;
	while (i < cmd->argc)
	{
		arg = cmd->argv[i];
		//check identifier
		if (!is_valid_identifier(arg, 1))
		{
			printf("bash: export: `%s': not a valid identifier\n", arg);
			//TODO set error to 1
			i++;
			continue;
		}
		set_env_var(get_keyval(arg), param);
		i++;
	}
}

void	bi_unset(t_command *cmd, t_param *param)
{
	int		i;
	int		j;
	char	*arg;

	i = 1;
	while (i < cmd->argc)
	{
		arg = cmd->argv[i];
		//check identifier
		if (!is_valid_identifier(arg, 0))
		{
			printf("bash: unset: `%s': not a valid identifier\n", arg);
			//TODO set error to 1
			i++;
			continue;
		}
		j = 0;
		while (j < param->envc)
		{
			if (ft_strcmp(arg, param->env[j]->key) == 0)
				unset_env_var(arg, param);
			j++;
		}
		i++;
	}
}