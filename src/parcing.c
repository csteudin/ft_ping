#include "../inc/ping.h"

/*
	- HANDLE HOSTS -
	+ checks if ip_str is empty, if empty parces is
	+ if existent, error
*/
	void handle_host(char *token)	{
		t_ping *ping = get_ping();

		if	(ping->ip_str == NULL)
			ping->ip_str = token;
		else
			ft_err("XXX: too many hosts", 1);
	}

/*
	- HANDLE FLAG -
	+ checks for verbose
	+ checks for help
	+ exits with other unexpected flags
*/
	void handle_flag(char *token)	{
		t_ping *ping = get_ping();
		
		if (strcmp(token, "-v") == 0)
			ping->verbose = true;
		else if	(strcmp(token, "-?") == 0)
			print_and_exit();
		else if	(token[0] == '-')
			ft_err("XXX: unknown flag\n", 1);
	}

/*
	- CHECK INPUT -
	+ checks for every string and parses it
	+ throws error if not expected
*/
	void check_input(int ac, char **av)
	{
		t_ping *ping = get_ping();

		if (ac < 2)
			ft_err("ping: usage error: Destination address required\n", 1);

		for (int i = 1; i < ac; i++)	{
			if	(av[i][0] == '-')
				handle_flag(av[i]);
			else
				handle_host(av[i]);
		}
		if (ping->ip_str == NULL)
			ft_err("XXX: destination required\n", 1);
	}