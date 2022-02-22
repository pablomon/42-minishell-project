#include "../inc/myshell.h"

#define DEBUG 0

/* returns the first expansion possible
or $ if not expansion possible */
char	*expand2(char *str, int *read, t_param *param)
{
	char	*var_name;
	char	*ret;

	if (DEBUG)
		printf("expand2: expand '%s'\n", str);
	if (str[0] == '?')
	{
		*read = *read + 1;
		return (ft_itoa(g_status));
	}
	if (!isvalidchar4var(str[0], 1))
	{
		if (DEBUG)
			printf("expand2: returning $\n");
		return (ft_strdup("$"));
	}
	var_name = NULL;
	while (str[*read] && isvalidchar4var(str[*read], 0))
	{
		var_name = ft_strjoinchar(var_name, str[*read]);
		*read = *read + 1;
	}
	if (DEBUG)
		printf("var name = %s\n", var_name);
	ret = mygetenv(var_name, param);
	if (ret == NULL)
		ret = ft_strdup("");
	else
		ret = ft_strdup(mygetenv(var_name, param));
	free(var_name);
	if (DEBUG)
		printf("expand2: res = '%s'\n", ret);
	return(ret);
}

char	*the_expanse(char *str, t_param *param)
{
	if (DEBUG)
		printf("the_expanse: Expanding '%s'...\n", str);
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
			res = expand2(&str[i + 1], &h, param);
			i += h + 1;
			tmp = expanded;
			expanded = ft_strjoin(expanded, res);
			free(res);
			free(tmp);
			continue;
		}
		expanded = ft_strjoinchar(expanded, str[i]);
		i++;
	}
	if (DEBUG)
		printf("the_expanse: result:\n'%s'\n", expanded);
	return (expanded);
}

void	expand_tokens(t_list *tkn_lst, t_param *param)
{
	if (DEBUG)
		printf("\nExpanding tokens..\n");
	int		i;
	t_list	*tmp;
	t_token	*t;
	char	*expanded;

	i = 0;
	tmp = tkn_lst;
	while (tmp)
	{
		t = (t_token*)(tmp->content);
		if (t->expandable)
		{
			if (DEBUG)
				printf("Expanding token '%s':\n", t->cnt);
			expanded = the_expanse(t->cnt, param);
			if (DEBUG)
				printf("Result: '%s'\n", expanded);
			free(t->cnt);
			((t_token*)(tmp->content))->cnt = expanded;
			// t->cnt = expanded;
			if (DEBUG)
				printf("New tkn->cnt after expansion: '%s'\n", ((t_token*)(tmp->content))->cnt);
		}
		tmp = tmp->next;
	}
	if (DEBUG)
		printf("\n...all tokens expanded\n");
}
