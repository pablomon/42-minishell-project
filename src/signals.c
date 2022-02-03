#include "../inc/myshell.h"
#include <signal.h>

void	parent_hdl(int signum)
{
	if (signum == SIGINT)
	{
		printf("Sigint parent\n");
		printf("($) ");
	}
	else if (signum == SIGQUIT)
	{
		printf("SIGQUIT parent\n");
	}
}

void	child_hdl(int signum)
{
	if (signum == SIGINT)
	{
		printf("Sigint child\n");
	}
	else if (signum == SIGQUIT)
	{
		printf("SIGQUIT child\n");
	}
}

void	reg_parent_signals()
{
	printf("registering parent signals...\n");
	signal(SIGINT, parent_hdl);
	signal(SIGQUIT, parent_hdl);
}

void	reg_child_signals()
{
	printf("registering child signals...\n");
	signal(SIGINT, child_hdl);
	signal(SIGQUIT, child_hdl);
}