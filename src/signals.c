#include "../inc/ping.h"

/*
    - SETUP SIGNALS -
*/
    void setup_signals() {
        struct sigaction action;

        bzero(&action, sizeof(action));
        action.sa_handler = handle_sigint;
        sigaction(SIGINT, &action, NULL);
    }

/*
    - HANDLE SIGINT -
*/
    void handle_sigint(int sig) {
        t_ping *ping = get_ping();
        double mixed_rtt = 0;
        double loss = 0;

        (void)sig;
        if (ping->received > 0)
            mixed_rtt = ping->mix_rtt / ping->received;
        if (ping->sequence > 0)
	        loss = ((double)(ping->sequence - ping->received) / (double)ping->sequence) * 100;
            
        printf("\n--- %s ping statistics ---\n", ping->domain);
        printf("%d packets transmitted, %d received, %.0f%% packet loss\n", ping->sequence, ping->received, loss);
        printf("rtt min/avg/max = %.3f/%.3f/%.3f ms\n", ping->min_rtt, mixed_rtt, ping->max_rtt);
    
        if (ping->sockfd >= 0)
            close(ping->sockfd);
        exit(0);
    }
