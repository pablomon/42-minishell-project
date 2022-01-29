#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char** environ;

void	setenvvar(char *var)
{
	static char **newenv = NULL;
	int i;
	int len;
	char **tmp;
	
	len = 0;
	while (environ[len] != NULL)
		len++;
	printf("len = %d\n", len);
	tmp = (char**)(malloc(sizeof(char*) * (len + 2)));
	i = 0;
	while (i < len)
	{
		tmp[i] = environ[i];
		i++;
	}
	tmp[len] = strdup(var);
	// ++++
	// free(environ); // error free invalid pointer
	// if (newenv != NULL)
		free(newenv);
	newenv = tmp;
	environ = newenv;
	// ++++
	i = 0;
	while (i < len + 1)
	{
		// printf("%i: %s\n", i, environ[i]);
		i++;
	}
}

int main(int argc, char const *argv[])
{

	char *newvar = "hi=HOLA!";
	setenvvar(newvar);
	printf("%s\n", getenv("hi"));

	newvar = "me=pablo";
	setenvvar(newvar);
	printf("%s\n", getenv("me"));

	free(environ);

	return 0;
}
