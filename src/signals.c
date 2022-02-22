#include "../inc/myshell.h"

void	parent_hdl(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	ft_putstr("\n");
	rl_redisplay();
}

void	child_hdl(int signum)
{

	if (signum == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 2);
}

void	reg_parent_signals()
{
	signal(SIGINT, parent_hdl);
	signal(SIGQUIT, SIG_IGN);
}

void	reg_child_signals()
{
	signal(SIGINT, child_hdl);
	signal(SIGQUIT, child_hdl);
}
