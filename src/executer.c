#include "../inc/myshell.h"

int	builtins(t_command *cmd, char **env)
{
	int	is_builtin;
	char *n;
	
	n = cmd->name;
	if (!ft_strcmp(n, "exit"))
	{
		exit(1);
	}
	else if (!ft_strcmp(n, "env"))
	{
		print_env(env);
		return (1);
	}
	return (0);
}

void	executer(char **env, t_token *tokens, t_command **cmd_lst)
{
	int			i;
	int			exec_count;

	printf("\nEXECUTER----\n");

	i = 0;
	exec_count = 0;
	while (cmd_lst[i] != NULL)
	{
		printf("Executing command %d:\n", i);
		if (!builtins(cmd_lst[i], env))
		{
			redirection(cmd_lst, env);
			new_process(cmd_lst[i], exec_count, env);
			if (cmd_lst[i]->fileout)
			{
				close(1);
				dup(1);
				dup(0);
			}
			dup2(1, 0);
		}
		i++;
	}
}