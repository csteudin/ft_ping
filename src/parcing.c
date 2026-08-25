#include "../inc/ping.h"

/*
    - HANDLE HOST -
    + checks if ip_str is empty, if empty parces it
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
			ft_err("ft_ping: too many hosts\n", 1);
	}

/*
	- CHECK FLAG -
	+ checks for flag type
	+ checks the input according to its own edgecases
	+ INTERVAL gets a floating point number check
*/
	void check_flag(char **av, int *i, t_flag flag)	{
		t_ping *ping = get_ping();
		char buf[256];

		if (flag == COUNT) {
			if (!av[*i + 1]) {
				ft_err("ft_ping: option requires an argument -- 'c'\n"
					"Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n", 1);
			}
			if (is_number(av[*i + 1])) {
				snprintf(buf, sizeof(buf), "ft_ping: invalid value (`%s' near `%s')\n",
						av[*i + 1], av[*i + 1]);
				ft_err(buf, 1);
			}
			ping->count = atoi(av[*i + 1]);
			if (ping->count <= 0) {
				snprintf(buf, sizeof(buf), "ft_ping: option value too small: %s\n", av[*i + 1]);
				ft_err(buf, 1);
			}
			(*i)++;
			}
		else if (flag == INTERVAL) {
			if (!av[*i + 1]) {
				ft_err("ft_ping: option requires an argument -- 'i'\n"
					"Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n", 1);
			}
			if (is_float(av[*i + 1])) {
				snprintf(buf, sizeof(buf), "ft_ping: invalid value (`%s' near `%s')\n",
						av[*i + 1], av[*i + 1]);
				ft_err(buf, 1);
			}
			ping->interval = strtod(av[*i + 1], NULL);
			if (ping->interval <= 0) {
				snprintf(buf, sizeof(buf), "ft_ping: option value too small: %s\n", av[*i + 1]);
				ft_err(buf, 1);
			}
			(*i)++;
		}
		else if (flag == TTL) {
			if (!av[*i + 1]) {
				ft_err("ft_ping: option requires an argument -- 't'\n"
					"Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n", 1);
			}
			if (is_number(av[*i + 1])) {
				snprintf(buf, sizeof(buf), "ft_ping: invalid value (`%s' near `%s')\n",
						av[*i + 1], av[*i + 1]);
				ft_err(buf, 1);
			}
			ping->ttl = atoi(av[*i + 1]);
			if (ping->ttl <= 0 || ping->ttl > 255) {
				snprintf(buf, sizeof(buf), "ft_ping: option value too big: %s\n", av[*i + 1]);
				ft_err(buf, 1);
			}
			(*i)++;
		}
		else if (flag == TOS) {
			if (!av[*i + 1]) {
				ft_err("ft_ping: option requires an argument -- 'T'\n"
					"Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n", 1);
			}
			if (is_number(av[*i + 1])) {
				snprintf(buf, sizeof(buf), "ft_ping: invalid value (`%s' near `%s')\n",
						av[*i + 1], av[*i + 1]);
				ft_err(buf, 1);
			}
			ping->tos = atoi(av[*i + 1]);
			if (ping->tos < 0 || ping->tos > 255) {
				snprintf(buf, sizeof(buf), "ft_ping: option value too big: %s\n", av[*i + 1]);
				ft_err(buf, 1);
			}
			(*i)++;
		}
	}

/*
    - HANDLE FLAG -
    + checks for verbose
    + checks for count      <bonus>
    + checks for interval   <bonus>
    + checks for ttl        <bonus>
    + checks for tos        <bonus>
    + checks for dontroute  <bonus>
    + checks for help
    + exits with other unexpected flags
*/
	void handle_flag(char *token, char **av, int *i)	{
		t_ping *ping = get_ping();
		char buf[256];

		if (strcmp(token, "-v") == 0)
			ping->verbose = true;
		else if (strcmp(token, "-c") == 0)
			check_flag(av, i, COUNT);
		else if (strcmp(token, "-i") == 0)
			check_flag(av, i, INTERVAL);
		else if (strcmp(token, "-t") == 0 || strcmp(token, "--ttl") == 0)
			check_flag(av, i, TTL);
		else if (strcmp(token, "-T") == 0)
			check_flag(av, i, TOS);
		else if (strcmp(token, "-r") == 0)
			ping->dontroute = true;
		else if	(strcmp(token, "-?") == 0)
			print_and_exit();
		else {
			snprintf(buf, sizeof(buf),
					"ft_ping: invalid option -- '%s'\n"
					"Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n",
					token + 1);
			ft_err(buf, 1);
		}
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
        ft_err("ft_ping: missing host operand\n"
               "Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n", 1);

		for (int i = 1; i < ac; i++) {
			if (ping->set_host && av[i][0] == '-')
				ft_err("ft_ping: option must precede host\n"
					"Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n", 1);
			if (strcmp(av[i], "--") == 0)
				ft_err("ft_ping: invalid option -- '-'\n"
					"Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n", 1);
			if (av[i][0] == '-' && av[i][1] != '\0')
				handle_flag(av[i], av, &i);
			else
				handle_host(av[i]);
		}
		if (ping->ip_str == NULL)
			ft_err("ft_ping: missing host operand\n"
				"Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n", 1);
	}


/*
    - VALID ICMP -
    + checks packet size, ip header, icmp type/code, id and checksum
    + rejects the packet if anything is off
    + only prints why if verbose is on
*/
	int valid_icmp(char *buf, int len)	{
		t_ping *ping = get_ping();
		struct ip *ip;
		t_icmp_header *icmp;

		if (len < (int)sizeof(struct ip))	{
			if (ping->verbose)
				printf("ft_ping: packet too small\n");
			return (0);
		}

		ip = (struct ip *)buf;

		if (ip->ip_hl < 5)	{
			if (ping->verbose)
				printf("ft_ping: invalid ip header length\n");
			return (0);
		}

		if ((size_t)len < (ip->ip_hl * 4 + sizeof(t_icmp_header)))	{
			if (ping->verbose)
				printf("ft_ping: truncated icmp packet\n");
			return (0);
		}

		icmp = (t_icmp_header *)(buf + (ip->ip_hl * 4));

		if (icmp->type != ICMP_ECHOREPLY)	{
			if (ping->verbose && icmp->type != ICMP_ECHO)
				printf("ft_ping: unexpected icmp type %d\n", icmp->type);
			return (0);
		}

		if (icmp->code != 0)	{
			if (ping->verbose)
				printf("ft_ping: unexpected icmp code %d\n", icmp->code);
			return (0);
		}

		if (ntohs(icmp->id) != (uint16_t)getpid())	{
			if (ping->verbose)
				printf("ft_ping: packet id mismatch\n");
			return (0);
		}

		if (checksum(icmp, len - (ip->ip_hl * 4)) != 0)	{
			if (ping->verbose)
				printf("ft_ping: invalid checksum\n");
			return (0);
		}

		return (1);
	}