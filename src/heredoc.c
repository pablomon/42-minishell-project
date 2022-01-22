#include "../inc/myshell.h"

void	ft_strapchar(char **str, char c)
{
	char	*new;
	int		i;
	char	cstr[2];

	if (str == NULL || *str == NULL)
		return;
	cstr[0] = c;
	cstr[1] = 0;
	new = ft_strjoin(*str, cstr);
	free(*str);
	*str = new;
}

/* returns the first expansion possible 
or $ if not expansion possible */
char	*expand(char *str, int *read)
{
	char	*error;
	char	var_name[1024];
	int		j;

	*read = 0;
	if (*str == '?')
	{
		*read = *read + 1;
		return (ft_itoa(errno));
	}
	if (!ft_isalpha(*str))
	{
		*read = *read + 1;
		return (ft_strdup("$"));
	}
	j = 0;
	while (str[*read] && ft_isalnum(str[*read]))
	{
		
		var_name[j] = str[*read];
		j++;
		*read = *read + 1;
	}
	var_name[j] = 0;
	printf("var name = %s\n", var_name);
	return (ft_strdup(getenv(var_name)));
}

char *heredoc_expander(char *str)
{
	printf("Heredoc Expansion:\n");
	char	*expanded;
	int		i;
	int		h;
	char	*tmp;
	char	*res;
	
	expanded = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			h = 0;
			char *res = expand(&str[i + 1], &h);
			printf("res %s\n", res);
			tmp = expanded;
			expanded = ft_strjoin(expanded, res);
			free(res);
			free(tmp);
			i += h + 1;
			continue;
		}
		ft_strapchar(&expanded, str[i]);
		i++;
	}
	printf("new heredoc:\n'%s'\n", expanded);
	return (expanded);
}

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
	return (heredoc);
}

char *read_heredoc(char **str, int *pos)
{
	ft_putstr("\n- Found HEREDOC -\n");
	char	*delim;
	char	*heredoc;
	char 	*expanded;

	// remove spaces
	while (ft_isspace((*str)[*pos]))
		*pos = *pos + 1;
	delim = ft_strdup("");
	while (((*str)[*pos]) && ((*str)[*pos]) != '\n')
	{
		ft_strapchar(&delim, (*str)[*pos]);
		*pos = *pos + 1;
	}
	printf("delimiter = \"%s\"\n", delim);
	heredoc = process_heredoc_input(delim);
	printf("heredoc:\n'%s'\n", heredoc);
	expanded = heredoc_expander(heredoc);
	printf("expanded heredoc:\n'%s'\n", expanded);
	free(heredoc);
	free(delim);
	return (expanded);
}