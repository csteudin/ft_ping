#include "../inc/ping.h"

void resolve_host() {
    t_ping *ping = get_ping();

    struct addrinfo hints;
    struct addrinfo *res;
    struct sockaddr_in *addr_in;
    int ret;

    bzero(&hints, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = 0; // SOCK_RAW on bare meddl
    hints.ai_protocol = IPPROTO_ICMP;

    ret = getaddrinfo(ping->domain, NULL, &hints, &res);
    if(ret != 0)    {
        fprintf(stderr, "XXX: %s: %s\n"
            , ping->domain, gai_strerror(ret));
    exit(1);
    }

    addr_in = (struct sockaddr_in *)res->ai_addr;
    ping->dest_addr = *addr_in;

    inet_ntop(AF_INET, &addr_in->sin_addr, ping->dest_ip, sizeof(ping->dest_ip));

    freeaddrinfo(res);
}