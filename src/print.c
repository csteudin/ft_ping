#include "../inc/ping.h"

/*
    - PRINT AND EXIT -
    + prints the formatted help section 
*/
    void	print_and_exit()    {
        printf("Usage: ft_ping [OPTION...] HOST ...\n");
        printf("Send ICMP ECHO_REQUEST packets to network hosts.\n");
        printf("\n");
        printf(" Options valid for all request types:\n");
        printf("\n");
        printf("  -c, --count=NUMBER         stop after sending NUMBER packets\n");
        printf("  -i, --interval=NUMBER      wait NUMBER seconds between sending each packet\n");
        printf("  -r, --ignore-routing       send directly to a host on an attached network\n");
        printf("  -T, --tos=NUM              set type of service (TOS) to NUM\n");
        printf("  -t, --ttl=N                specify N as time-to-live\n");
        printf("  -v, --verbose              verbose output\n");
        printf("\n");
        printf("  -?, --help                 give this help list\n");
        printf("      --usage                give a short usage message\n");
        printf("\n");
        printf("Mandatory or optional arguments to long options are also mandatory or optional\n");
        printf("for any corresponding short options.\n");
        exit(0);
    }

/*
    - PRINT START -
    + prints the initial "PING host (ip): n data bytes" line
*/
    void print_start()  {
        t_ping *ping = get_ping();

        printf("PING %s (%s): 56 data bytes\n", ping->domain, ping->dest_ip);
    }

/*
    - PRINT STATS -
    + prints transmitted/received/loss and the rtt line
    + gets called both on normal end and on ctrl+c
*/
    void print_stats()  {
        t_ping *ping = get_ping();
        double mixed_rtt = 0;
        double loss = 0;

        if (ping->received > 0)
            mixed_rtt = ping->mix_rtt / ping->received;
        if (ping->sequence > 0)
        loss = ((double)(ping->sequence - ping->received) / (double)ping->sequence) * 100;

        printf("\n--- %s ping statistics ---\n", ping->domain);
        printf("%d packets transmitted, %d received, %.0f%% packet loss\n",
            ping->sequence, ping->received, loss);
        if (ping->received > 0)
            printf("rtt min/avg/max = %.3f/%.3f/%.3f ms\n", ping->min_rtt, mixed_rtt, ping->max_rtt);
    }