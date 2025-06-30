#include "ping.h"

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

int check_input(int ac, char **av)
{
	if (ac == 1)
}

int main(int ac, char **av)
{
	if (check_input(ac, av))

	return (0);
}