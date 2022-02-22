#include "../inc/myshell.h"

int	is_valid_identifier(char *arg, int allow_equalsign)
{
	int i;

	if (isvalidchar4var(arg[0], 1))
	{
		i = 1;
		while (isvalidchar4var(arg[i], 0))
			i++;
		if (allow_equalsign && (arg[i] == '=' || arg[i] == 0))
			return (1);
		if (!allow_equalsign && arg[i] == 0)
			return (1);
	}
	return (0);
}

void	bi_export(t_command *cmd, t_param *param, int is_child)
{
	int i;
	int j;
	char	*arg;

	i = 1;
	if (cmd->argc == 1 && is_child)
	{
		print_export(param);
		return;
	}
	while (i < cmd->argc && !is_child && param->cmdc == 1)
	{
		arg = cmd->argv[i];
		//check identifier
		if (!is_valid_identifier(arg, 1))
		{
			printf("minishell: export: '%s': not a valid identifier\n", arg);
			g_status = 1;
			i++;
			continue;
		}
		set_env_var(get_keyval(arg), param);
		i++;
	}
}

int	bi_pwd(int ischild)
{
	char	*buf;

	if (!ischild)
		return (0);
	buf = getcwd(NULL, 0);
	ft_putstr(buf);
	ft_putstr("\n");
	free(buf);
	return (0);
}

static int	is_n_option(char *argv)
{
	if (!argv || ft_strlen(argv) == 0)
		return (0);
	if (argv && *argv == '-')
	{
		argv++;
		while (*argv == 'n')
			argv++;
	}
	if (argv && *argv == '\0')
		return (1);
	return (0);
}

/* remove spaces extern spaces */
char	*trim_str(char *str)
{
	int	i;
	int lft;
	int rgt;
	char	*new;

	new = ft_strdup("");
	lft = 0;
	while (ft_isspace(str[lft]))
		lft++;
	rgt = ft_strlen(str) - 1;
	while (ft_isspace(str[rgt]))
		rgt--;
	i = lft;
	while (i <= rgt)
	{
		new = ft_strjoinchar(new, str[i]);
		i++;
	}
	return (new);
}

int	bi_echo(t_command *cmd, int ischild)
{
	int		new_l;
	int		i;
	char	*out;
	char	*tmp;
	char	*trimmed;

	print_arr(cmd->argv);
	g_status = 0;
	if (!ischild)
		return (0);
	out = ft_strdup("");
	new_l = 1;
	i = -1;
	while (is_n_option(cmd->argv[++i + 1]))
		new_l = 0;
	while (i < cmd->argc && cmd->argv[++i] && ft_strlen(cmd->argv[i])!=0)
	{
		trimmed = trim_str(cmd->argv[i]);
		tmp = out;
		out = ft_strjoin(out, trimmed);
		free(trimmed);
		free(tmp);
		if (cmd->argv[i + 1] && ft_strlen(cmd->argv[i + 1]) != 0)
			out = ft_strjoinchar(out, ' ');
	}
	ft_putstr_fd(out, 1);
	if (new_l)
		ft_putchar_fd('\n', 1);
	free(out);
	return (0);
}
