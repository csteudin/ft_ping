#include "../inc/ping.h"

/*
    - SETUP SOCKET -
    + sets up a raw socket ( neccesary for selfmade icmp )
    + sets up the ttl for packages send ny this socket
    + IF -t takes the given ttl, else takes 64 <standard>
    + also sets tos and dontroute if those flags were given
*/
    void setup_socket() {
        t_ping *ping = get_ping();
        int ttl;
        int one = 1;
        char buf[256];

        ping->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
        if (ping->sockfd < 0) {
            snprintf(buf, sizeof(buf), "ft_ping: socket: %s\n", strerror(errno));
            ft_err(buf, 1);
        }
        ttl = ping->ttl;
        if (setsockopt(ping->sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0) {
            snprintf(buf, sizeof(buf), "ft_ping: setsockopt: %s\n", strerror(errno));
            ft_err(buf, 1);
        }
        if (ping->tos >= 0) {
            int tos = ping->tos;
            if (setsockopt(ping->sockfd, IPPROTO_IP, IP_TOS, &tos, sizeof(tos)) < 0) {
                snprintf(buf, sizeof(buf), "ft_ping: setsockopt(IP_TOS): %s\n", strerror(errno));
                ft_err(buf, 1);
            }
        }
        if (ping->dontroute) {
        if (setsockopt(ping->sockfd, SOL_SOCKET, SO_DONTROUTE, &one, sizeof(one)) < 0) {
            snprintf(buf, sizeof(buf), "ft_ping: setsockopt(SO_DONTROUTE): %s\n", strerror(errno));
            ft_err(buf, 1);
        }
    }
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
        char err_buf[256];

        bzero(&hints, sizeof(struct addrinfo));

        hints.ai_family = AF_INET;
        hints.ai_socktype = 0; // SOCK_RAW on bare meddl || SOCK_DGRAM
        hints.ai_protocol = IPPROTO_ICMP;

        ret = getaddrinfo(ping->domain, NULL, &hints, &res);
        if (ret != 0) {
            snprintf(err_buf, sizeof(err_buf), "ft_ping: %s: %s\n",
                    ping->domain, gai_strerror(ret));
            ft_err(err_buf, 1);
        }

        addr_in = (struct sockaddr_in *)res->ai_addr;
        ping->dest_addr = *addr_in;

        inet_ntop(AF_INET, &addr_in->sin_addr, ping->dest_ip, sizeof(ping->dest_ip));

        freeaddrinfo(res);
    }