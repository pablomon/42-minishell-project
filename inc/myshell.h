/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:01:48 by lvintila          #+#    #+#             */
/*   Updated: 2022/02/20 14:30:14 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSHELL_H
# define MYSHELL_H
# include <termios.h>
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
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"

# define STDIN 0
# define STDOUT 1

# define RL_BUFF_SIZE 1024
# define TK_BUFF_SIZE 64

/*
ANSI Color codes
 */
# define RED   		"\033[0;31m"
# define YELLOW 		"\033[0;33m"
# define CYAN 		"\033[0;36m"
# define GREEN 		"\033[0;32m"
# define BLUE 		"\033[0;34m"
# define INVERT		"\033[0;7m"
# define RESET  		"\e[0m"
# define BOLD		"\e[1m"
# define ITALICS		"\e[3m" 

# define SHLNAME		"minishell"

typedef struct	s_keyval
{
	char	*key;
	char	*val;
}				t_keyval;

typedef struct  s_param
{
	int			default_in;
	int			default_out;
	int			fd_in;
	int 		fd_out;
	char		*line;
	int			cmdc; // num of commands 
	t_keyval	**env;
	int			envc; // num of env variables
	int			envvalc; // num of env varirables with value, usado para generar el envp
	int			process_status;
	char		*prompt;
	t_list		*tkn_lst;
	t_list		*cmd_lst;

}               t_param;


typedef struct s_token
{
	char*	cnt;
	int		type;
	int		op_type;
	int		delimited;
	int		expandable;
}			t_token;

typedef struct s_fileout
{
	char	*file;
	t_token	*filetkn;
	int		append;
}				t_fileout;

typedef struct s_command
{
	int		is_assignment;
	char*	name;
	int		argc;
	char**	argv;
	t_list	*arglst;
	char*	filein;
	t_token	*fileintkn;
	char*	lastfileout;
	t_token	*lastfileouttkn;
	int		fileoutc;
	t_list	*fileouts;
	int		append;
	char*	hdocword;
	t_token	*hdoctkn;
	int		piped;
}			t_command;

# define RET 1
# define SKIP 2

typedef struct s_tokenizer
{
	char*	cnt;
	char	c;
	char	prev;
	int		quoted;
	int		heredoc;
	int		spos;
	int		tpos;
	int		action;
	int		expand_hd;
	int		ruleres;
	char	*str;
}			t_tokenizer;

/* Errors */
#define NODIR 7
#define NOPERM 8
#define NOCMD 9
#define DUP_ERR 10
#define PIPEND_ERR 11
#define PIPE_ERR 12
#define FORK_ERR 13
#define MEM_ERR 14
#define IS_DIR 15
#define NOT_DIR 16

int				g_status;
void	*my_perror(t_param *param, int err_type, char *str, int errnum);

/* Shell functions*/
int         myshell_loop(t_param *param, char **av);
void		update_prompt(t_param *param);

/* Clean up */
void		free_tokens(t_list *tknlst);
void		free_commands(t_list *commands);
void		cleanup(t_param *param);

/* Lexer */
# define TOK_DELIM " >\t\r\n\a"

# define TT_EMPTY 0
# define TT_OP 1
# define TT_WORD 2
# define TT_EOF 3
 
# define NOQUOTE 0
# define SQUOTE 1
# define DQUOTE 2
 
# define OT_PIPE 1
# define OT_IRED 2
# define OT_ORED 3
# define OT_ORED2 4
# define OT_HEREDOC 5
# define OT_NEWLINE 6

t_list		*get_tokens(char *input, t_param *param);
void		init_tokenizer_struct(t_tokenizer *d, int heredoc, int pos, char *str);
void		tokenize(t_tokenizer *d, t_token *token, t_param *param);
int			delim_op_rules(t_tokenizer *data, t_token *token, char *str);
int			quote_rules(t_tokenizer *data, t_token *token, char *str);
int			mark_exp_rules(t_tokenizer *data, t_token *token, char *str);
int			newop_rules(t_tokenizer *data, t_token *token, char *str);
int			word_rules(t_tokenizer *data, t_token *token, char *str);
int			delimit_tkn(t_tokenizer *data, t_token *tkn);
int			is_op(char c);

/* Expander */
void		expand_tokens(t_list *tkn_lst, t_param *param);
char		*the_expanse(char *str, t_param *param);

/* Heredoc */
char		*read_heredoc(char *str, t_tokenizer *d, t_token *tkn);

/* Parser */
t_list		*parser(t_list *tknlst, t_param *param);
t_command	*new_command(int max_args);
void		argv_append(t_command *cmd, t_token *newargtkn);
void		add_fileout(t_command *cmd, t_token *file, int operator);

/* Executer */
void		executer(char **env, t_token *tokens, t_command **cmd_lst);
int		cmd_execute(t_list *cmd_list, t_param *param);


/* Built ins*/
int			is_valid_identifier(char *arg, int allow_equalsign);
void		bi_exit(t_command *cmd, t_param *param, int ischild, int cmd_num);
void		bi_env(t_param *param, int ischild);
void		bi_export(t_command *cmd, t_param *param, int ischild);
void		bi_unset(t_command *cmd, t_param *param, int ischild);
void		bi_cd(t_command *cmd, t_param *param, int ischild);
int			bi_echo(t_command *cmd, int ischild);
int			bi_pwd(int ischild);

/* diffrent utility functions */
char        space_tab(unsigned int i, char c);
char        **parse(char *buff);
int         get_cmd(t_param *param);
char        *rl_gets(t_param *param);
char        *find_path(char *cmd, char **envp);
void        check_str(char *str, char *cmd, t_param *param);
void        free_arr(char **arr);
int         found_char(char *str, char c);
int			try_bis(t_command *cmd, t_param *param, int ischild, int cmd_num);

/* environment */
t_keyval	*get_keyval(char *str);
int			try_set_existing_var(t_keyval *var, t_param *param);
void		set_env_var(t_keyval *var, t_param *param);
void		unset_env_var(char *name, t_param *param);
char		*mygetenv(char *name, t_param *param);
char		**make_envp(t_param *param);
void		print_export(t_param *param);
void		my_setenv(char *name, char *value, t_param *param);

/* signals */
void	reg_parent_signals();
void	reg_child_signals();

/* utils */
// l
int		ft_arr_len(char **arr);
int		ft_strchr_i(const char *s, int c);
char	**ft_extend_arr(char **in, char *new_str);
char	**ft_dup_arr(char **arr);
char	**ft_arr_replace_in(char ***big, char **small, int n);
void	ft_free_arr(char ***arr);
int		ft_put_arr_fd(char **arr, int fd);
// p
void	emptyfunc(void *v);
int		isvalidchar4var(char c, int is_start);
char	*ft_strjoinchar(char *str, char c);
size_t	ft_wordcount(char const *str, char delimiter);
t_list	*ft_lstat(t_list *lst, int pos);

/* debug */
void	print_arr(char **arr);
void	print_tkn(t_token *tkn);
void	print_cmd(t_command *cmd);

#endif
