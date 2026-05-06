#include "../inc/ping.h"

/*
	- HANDLE HOSTS -
	+ checks if ip_str is empty, if empty parces is
	+ if existent, error
*/
	void handle_host(char *token)	{
		t_ping *ping = get_ping();

		if	(ping->ip_str == NULL)	{
			ping->ip_str = token;
			strncpy(ping->domain, token, sizeof(ping->domain) - 1);
			ping->domain[sizeof(ping->domain) - 1] = '\0';
			ping->set_host = true;
		}
		else
			ft_err("XXX: too many hosts", 1);
	}

/*
	- CHECK FLAG -
	+ checks for flag type
	+ checks the input according to its own edgecases
	+ INTERVAL gets a floating point number check
*/
	void check_flag(char **av, int *i, t_flag flag)	{
		t_ping *ping = get_ping();

		if (flag == COUNT)	{
			if (!av[*i + 1])
				ft_err("XXX: option requires argument -- \"c\"\n", 1);
			if(is_number(av[*i + 1]))
				ft_err("XXX: valid numeric argument required\n", 1);
			ping->count = atoi(av[*i + 1]);
			if (ping->count <= 0)
				ft_err("XXX: invalid numeric argument \"c\"\n", 1);
			(*i)++;
		}
		else if (flag == INTERVAL)	{
			if (!av[*i + 1])
				ft_err("XXX: option requires argument -- \"i\"\n", 1);
			if(is_float(av[*i + 1]))
				ft_err("XXX: numeric argument required\n", 1);
			ping->interval = strtod(av[*i + 1], NULL);
			if (ping->interval <= 0)
				ft_err("XXX: invalid numeric argument \"i\"\n", 1);
			(*i)++;
		}
		else if (flag == TTL)	{
			if (!av[*i + 1])
				ft_err("XXX: option requires argument -- \"t\"\n", 1);
			if(is_number(av[*i + 1]))
				ft_err("XXX: numeric argument required\n", 1);
			ping->ttl = atoi(av[*i + 1]);
			if (ping->ttl <= 0 || ping->ttl > 255)
				ft_err("XXX: invalid numeric argument \"t\"\n", 1);
			(*i)++;
		}
	}

/*
	- HANDLE FLAG -
	+ checks for verbose
	+ checks for count		<bonus>
	+ checks for interval	<bonus>
	+ checks for ttl		<bonus>
	+ checks for help
	+ exits with other unexpected flags
*/
	void handle_flag(char *token, char **av, int *i)	{
		t_ping *ping = get_ping();
		
		if (strcmp(token, "-v") == 0)
			ping->verbose = true;
		else if (strcmp(token, "-c") == 0)
			check_flag(av, i, COUNT);
		else if (strcmp(token, "-i") == 0)
			check_flag(av, i, INTERVAL);
		else if (strcmp(token, "-t") == 0)
			check_flag(av, i, TTL);
		else if	(strcmp(token, "-?") == 0)
			print_and_exit();
		else
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
			if	(ping->set_host && av[i][0] == '-')
				ft_err("XXX: option must precede host\n", 1);

			if	(strcmp(av[i], "--") == 0)
				ft_err("XXX: invalid option \"--\"\n", 1);

			if	(av[i][0] == '-' && av[i][1] != '\0')
				handle_flag(av[i], av, &i);
			else
				handle_host(av[i]);
		}
		if (ping->ip_str == NULL)
			ft_err("XXX: destination required\n", 1);
	}
