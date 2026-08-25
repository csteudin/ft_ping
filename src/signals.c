#include "../inc/ping.h"

/*
    - SETUP SIGNALS -
    + registers our sigint handler
*/
    void setup_signals() {
        struct sigaction action;

        bzero(&action, sizeof(action));
        action.sa_handler = handle_sigint;
        sigaction(SIGINT, &action, NULL);
    }

/*
    - HANDLE SIGINT -
    + prints stats, closes the socket, exits clean
*/
    void handle_sigint(int sig) {
        t_ping *ping = get_ping();

        print_stats();

        if (ping->sockfd >= 0)
            close(ping->sockfd);
        exit(0);
    }
