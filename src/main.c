#include "../inc/ping.h"

/* * REQUIREMENTS *
* - inetutils-2.0 ping = reference
* - -v and -? (Mandatory) | bonus?
* - do not perform dns resolution in packet return
* - socket(IPV4, SOCK_RAW, ICMP protocol)
* */

/* _MODULES_ *
- PARSING
- SOCKET COMMUNICATION
- SIGNAL HANDLING AND TIME TRACKING LOOP (MAIN)
- STATISTICS AND PRINTING
*/

/*
	- INITIALIZE -
*/
void initialize()	{
	t_ping *ping;

	ping = get_ping();
	bzero(ping, sizeof(t_ping));
	ping->ip_str = NULL;
	ping->domain = NULL;
}

/*
	- MAIN -
	+ checks input
*/
int main(int ac, char **av)
{
	check_input(ac, av);




	return (0);
}