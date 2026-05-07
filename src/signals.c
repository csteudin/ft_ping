#include "../inc/ping.h"

/*
    - HANDLE SIGINT -
*/
    void handle_sigint(int sig) {
        t_ping *ping = get_ping();
        double mixed_rtt = 0;

        (void)sig;
        if (ping->received > 0)
            mixed_rtt = ping->mix_rtt / ping->received;
        printf("\n--- %s ping statistics ---\n", ping->domain);
    
        printf("%d packets transmitted, %d received\n", ping->sent, ping->received);

        printf("rtt min/avg/max = %.3f/%.3f/%.3f ms\n", ping->min_rtt, mixed_rtt, ping->max_rtt);
    
        close(ping->sockfd);
        exit(0);
    }
