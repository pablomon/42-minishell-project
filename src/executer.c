#include "../inc/myshell.h"

#include <signal.h>
int	try_builtins(t_command *cmd, t_param *param)
{
	int	ret;

	ret = 1;
	if (!ft_strcmp(cmd->name, "exit"))
		bi_exit(cmd, param);
	else if (!ft_strcmp(cmd->name, "env"))
		bi_env(param);
	else if (!ft_strcmp(cmd->name, "export"))
		bi_export(cmd, param);
	else if (!ft_strcmp(cmd->name, "unset"))
		bi_unset(cmd, param);
	else
		ret = 0;
	return (ret);
}

void cmd_execute(t_command **cmd, t_param *param)
{
	pid_t	child_pid;
	int		i;
	int		fd_pipe[2];
	char	*file;
	int		status;

	printf("\nEXECUTER----\n");
	status = 0;
//	file = NULL;
	param->tmp_in = dup(0);
	param->tmp_out = dup(1);
	/* set the initial input */
	if (cmd[0]->filein)
	{
		param->fd_in = open(cmd[0]->filein, O_RDONLY);
		if (param->fd_in < 0)
		{
			perror("Error(file_in): ");
			return ;
		}
	} 
	else /* use default input */
		param->fd_in = dup(param->tmp_in);
	i = 0;
	while (i < param->cmds) /* cmd_argc is numofsimplecommands */
	{
		/* paso aquí los built ins porque cualquier comando puede ser
		built in, no solo el primero */
		if (try_builtins(cmd[i], param))
		{
			i++;
			continue;
		}

		/* redirect input */
		dup2(param->fd_in, 0);
		close(param->fd_in);
		/* setup output */	
		if (i == param->cmds - 1) /* cmd_argc is numofsimplecommands */
		{
			if (cmd[i]->fileout)
			{
				if (cmd[i]->append == 0)
					param->fd_out = open(cmd[i]->fileout, O_CREAT | O_WRONLY | O_TRUNC, 0664);
				else if (cmd[i]->append != 0)
					param->fd_out = open(cmd[i]->fileout, O_CREAT | O_WRONLY | O_APPEND, 0664); 
			}
			else	
				/* use default output */
				param->fd_out = dup(param->tmp_out);
		}
		else
		{
			pipe(fd_pipe);
			param->fd_out = fd_pipe[1];
			param->fd_in = fd_pipe[0];
		}
		/* redirect output */
		dup2(param->fd_out, 1);
		close(param->fd_out);

		reg_child_signals();
 		child_pid = fork();
		if (child_pid == 0)
		{
 			if (access(cmd[i]->argv[0], F_OK) == 0)
				file = cmd[i]->argv[0];
			else
				file = find_path(cmd[i]->argv[0], param);
			char **envp = make_envp(param);
			if (execve(file, cmd[i]->argv, envp) == -1)
				check_str(file, cmd[i]->argv[0]);
			// TODO Podemos hacer un free_arr(envp); ???
		}
		else
		{
			wait(NULL);
			reg_parent_signals();
		}
		i++;
		printf("Command %d executed\n", i);
	} /* while */
	/* restore in  / out defaults */

 	dup2(param->tmp_in, 0);
	dup2(param->tmp_out, 1);
	close(param->tmp_in);
	close(param->tmp_out);
	waitpid(child_pid, &status, 0);
}