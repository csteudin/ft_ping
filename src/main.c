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
	+ BONUS +

	-c <count>
	-i <interval>
	-t <ttl>
*/

/*
	- INITIALIZE -
*/
	void initialize()	{
		t_ping *ping;

		ping = get_ping();
		bzero(ping, sizeof(t_ping));
		ping->ip_str = NULL;
		ping->count = -1;
		ping->sockfd = -1;
		ping->interval = 1.0;
		ping->ttl = 64;
		ping->sequence = 0;
	}

/*
	- MAIN -
	+ checks input
*/
	int main(int ac, char **av)
	{
		initialize();
		check_input(ac, av);
		resolve_host();
		setup_socket();
		send_ping();
		receive_ping();
		//send loop
		//recv loop
		//print

		return (0);
	}