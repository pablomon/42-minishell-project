#include "../inc/myshell.h"
#define DEBUG 0

char	*process_heredoc_input(char *delim)
{
	char	*line;
	char	*heredoc;
	char	*tmp;

	heredoc = ft_strdup("");
	line = ft_strdup("");
	while (1)
	{
		free(line);
		line = readline("> ");
		if (ft_strcmp(line, delim) == 0)
			break;
		if (ft_strcmp(heredoc, "") != 0)
		{
			tmp = heredoc;
			heredoc = ft_strjoin(heredoc, "\n");
			free(tmp);
		}
		tmp = heredoc;
		heredoc = ft_strjoin(heredoc, line);
		free(tmp);
	}
	free(line);
	heredoc = ft_strjoinchar(heredoc, '\n');
	return (heredoc);
}

char	*read_heredoc(char *str, t_tokenizer *d, t_token *tkn)
{
	if (DEBUG)
		ft_putstr("\n- Found HEREDOC -\n");
	char	*delim;
	char	*heredoc;

	tkn->expandable = 1;
	while (ft_isspace((str)[d->spos]))
		d->spos++;
	delim = ft_strdup("");
	while (((str)[d->spos]) && ((str)[d->spos]) != '\n')
	{
		if (str[d->spos] == '\'' || str[d->spos] == '"')
		{
			tkn->expandable = 0;
			d->spos++;
			continue;
		}
		delim = ft_strjoinchar(delim, (str)[d->spos]);
		d->spos++;
	}
	if (DEBUG)
		printf("delimiter = \"%s\"\n", delim);
	heredoc = process_heredoc_input(delim);
	if (DEBUG)
		printf("heredoc:\n'%s'\n", heredoc);
	free(delim);
	return (heredoc);
}
