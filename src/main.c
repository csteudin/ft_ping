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
		ping->received = 0;
		ping->min_rtt = 0;
		ping->max_rtt = 0;
		ping->mix_rtt = 0;
	}

/*
	- PING LOOP -
*/
	void ping_loop()	{
		t_ping *ping = get_ping();
		struct timeval t_send, t_now;
		double elapsed, remaining;

		while(ping->count == -1 || ping->sequence < ping->count)
		{
			gettimeofday(&t_send, NULL);
			send_ping();

			receive_ping(ping->interval);

			gettimeofday(&t_now, NULL);
			elapsed = (t_now.tv_sec - t_send.tv_sec)
                + (t_now.tv_usec - t_send.tv_usec) / 1000000.0;
        	remaining = ping->interval - elapsed;

			if (remaining > 0)
				usleep((useconds_t)(remaining * 1000000));
		}
		print_stats();
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

		print_start();
		
		setup_signals();
		
		ping_loop();

		return (0);
	}