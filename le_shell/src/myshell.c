/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:55:41 by lvintila          #+#    #+#             */
/*   Updated: 2022/01/04 17:02:36 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"

// int main(int ac, char *av[], char **env)
// {
// 	int execution_coun = 1;
// 	int status = 0;
// 	(void)ac;

// 	if (ac > 1)
// 	{
// 		write(2, "Error: wrong number of arguments\n", 33);
// 		write(2, "Usage: ./minishell\n", 19);
// 		return (0);
// 	}

// 	status = myshell_loop(av, execution_coun, env);
// 	return (status);
// }

int main(int argc, char *argv[])
{
	char		*cmd_line;
	char		*tmp;
	t_token		*tokens;
	t_command	**cmd_lst;

	while (1)
	{
		tmp = readline("$> ");
		cmd_line = ft_strjoin(tmp, "\n"); //TODO ser capaz de leer newline al final
		free (tmp);
		
		tokens = tokenizer(cmd_line);

		for (int i = 0; i < 200; i++)
		{
			if (tokens[i].type == TT_EOF)
			{
				printf("Token %d: EOF\n", i);
				break;
			}
			else
				printf("Token %d: '%s'\n", i, tokens[i].cnt);
		}

		cmd_lst = parser(tokens);
		printf("\nParse result:\n");
		int i = 0;
		while (cmd_lst[i] != NULL)
		{
			printf("Command %d:\n", i);
			print_cmd(cmd_lst[i]);
			i++;
		}

		printf("free tokens\n");
		free(tokens);
	}

	return 0;
}
