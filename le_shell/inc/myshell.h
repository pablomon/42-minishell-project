/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:01:48 by lvintila          #+#    #+#             */
/*   Updated: 2022/01/04 17:02:08 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSHELL_H
# define MYSHELL_H
# include <stdio.h>
# include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"

# define STDIN 0
# define STDOUT 1

/* Tokens */
#define TT_EMPTY 0
#define TT_OP 1
#define TT_WORD 2
#define TT_EOF 4

#define NOQUOTE 0
#define SQUOTE 1
#define DQUOTE 2

#define OT_PIPE 1
#define OT_IRED 2
#define OT_ORED 3
#define OT_ORED2 4
#define OT_HEREDOC 5

typedef struct s_token
{
	char*	cnt;
	int		type;
	int		op_type;
	int		delimited;
}			t_token;

t_token *tokenizer(char *input);
int	expander(char **text, int pos);
int is_op(char c);

char	*ft_strreplace(char *str, char *insert, int pos, int len);

/* Commands */
typedef struct s_command
{
	char*	name;
	int		argc;
	char**	argv;
	char*	filein;
	char*	fileout;
	int		append;
	char*	hdocword;
}			t_command;

t_command	**parser(t_token *tokens);
void		print_cmd(t_command *cmd);

/**/
char *line;

/* Shell functions*/
int myshell_loop(char *av[], int execution_counter, char **env);
int new_process(char *av[], int execution_counter, char **env);

/* diffrent utility functions */
void	print_env(char **env);
char    *rl_gets();

char    space_tab(unsigned int i, char c);
char    **parse(char *buff);
int     get_cmd();
void    redirect(char *buff);
int     execute(char *buff, char **envp);
char    *rl_gets();
char    *find_path(char *cmd, char **envp);
void    check_str(char *str, char *cmd);
void    free_arr(char **arr);

#endif
