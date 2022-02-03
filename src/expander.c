#include "../inc/myshell.h"

#define VERBOSE 0

char	*ft_strreplace(char *str, char *insert, int pos, int len)
{
	char	*s1;
	char	*s2;
	char	*new;

	if (VERBOSE)
		printf("replace:");
	s1 = calloc(pos + 1, sizeof(char));
	s1 = ft_strncpy(s1, str, pos);
	if (insert == NULL)
		s2 = ft_strdup(s1);
	else
		s2 = ft_strjoin(s1, insert);
	new = ft_strjoin(s2, &(str[pos + len + 1]));
	free(s1);
	free(s2);
	return (new);
}

int	expander(char **text, int pos, t_param *param)
{
	if (VERBOSE)
		printf("Expander:\n");
	char	var_name[ft_strlen(*text) + 1];
	int		len;
	char	*str;

	str = &(*text)[pos];
	len = 0;
	if (str[1] == '?')
	{
		if (VERBOSE)
			printf("TODO $? value\n");
		char *serror = ft_itoa(errno);
		*text = ft_strreplace(*text, serror, pos, ft_strlen(serror));
		free(serror);
		return(0);
	}
	if (!ft_isalpha(str[1]))
	{
		if (VERBOSE)
			printf("No alpha after $ (%c)\n", str[1]);
		return (-1);
	}
	while (str[len + 1] && ft_isalnum(str[len + 1]))
	{
		var_name[len] = str[len + 1];
		len++;
	}
	var_name[len] = 0;

	if (VERBOSE)
		printf("env var %s = ", var_name);

	if (mygetenv(var_name, param) != NULL)
		if (VERBOSE)
			printf("%s\n",mygetenv(var_name, param));
	else
		if (VERBOSE)
			printf("\n");
	char *tmp = *text;
	*text = ft_strreplace(*text, mygetenv(var_name, param), pos, len);
	// free (tmp);
	return (0);
}