
/*
SIGINT and SIGQUIT are intended specifically for requests from the terminal: 
particular input characters can be assigned to generate these signals (depending on the terminal control settings). 
The default action for SIGINT is the same sort of process termination as the default action for SIGTERM 
and the unchangeable action for SIGKILL; the default action for SIGQUIT is also process termination, 
but additional implementation-defined actions may occur, such as the generation of a core dump. 
Either can be caught or ignored by the process if required.

SIGQUIT = ctrl+/ o ctrl+ç en español -> 
SIGINT = ctrl+D ( cntrl+C linux ) -> terminates the process


*/
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void sigint_hdl(int signum)
{
	if (signum == SIGINT)
	{
		// kill foreground process
		printf("terminar lo q se esté haciendo y mostrar nueva linea");
	}
	else if (signum == SIGQUIT)
	{
		printf("no hacer nada");
	}
}

int main(void)
{
	// signal(SIGINT, sigint_hdl);
	// signal(SIGQUIT, sigint_hdl);
	printf("Gellloooo");
	while (1)
	{
		usleep(300000);
		write(1,".",1);
	}


	return 0;
}
