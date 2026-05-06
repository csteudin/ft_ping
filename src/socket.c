#include "../inc/ping.h"

/*
    - SETUP SOCKET -
    + sets up a raw socket ( neccesary for selfmade icmp )
    + sets up the ttl for packages send ny this socket
    + IF -t takes the given ttl, else takes 64 <standard>
*/
    void setup_socket() {
        t_ping *ping = get_ping();
        int ttl;

        ping->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
        if (ping->sockfd < 0)
            ft_err("XXX: socket: Operation not permitted\n", 1);
        ttl = ping->ttl;
        if (setsockopt(ping->sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
            ft_err("XXX: setsockopt TTL failed\n", 1);
    }
/*
    - RESOLVE HOST -
    + creates addrinfo struct, with corresponding setup for ipv4
    + checks if the provided domain is existing
    + extracts the destination adress
*/
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