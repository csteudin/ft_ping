#include "../inc/ping.h"

/*
    - CHECKSUM -
    + calculates the checksum and returns the sum
    + we then check if it is the same checksum
    + always creates the checksum for the whole ICMP header
    +
*/
    uint16_t checksum(void *buf, int len)
    {
        uint16_t    *data = buf;
        uint32_t    sum = 0;

        while (len > 1)
        {
            sum += *data++;
            len -= 2;
        }
        if (len == 1)
            sum += *(uint8_t *)data;
        sum = (sum >> 16) + (sum & 0xffff);
        sum += (sum >> 16);
        return (~sum);
    }

/*
    - SEND PING -
    + sends the ICMP header with the timeval as payload
    + 
*/
    void send_ping()    {
        t_ping *ping = get_ping();
        t_icmp_header   packet;
        struct timeval  time;

        bzero(&packet, sizeof(packet));
        packet.type = ICMP_ECHO;
        packet.code = 0;
        packet.id = (uint16_t)getpid();
        packet.sequence = ping->sequence++;
        gettimeofday(&time, NULL);
        memcpy(packet.payload, &time, sizeof(time));
        packet.checksum = checksum(&packet, sizeof(packet));

        if (sendto(ping->sockfd, &packet, sizeof(packet), 0, \
            (struct sockaddr *)&ping->dest_addr, sizeof(ping->dest_addr)) < 0)
            ft_err("XXX: sendto failed\n", 1);
        ping->sent++;
    }

/*
    - RECEIVE PING -
*/
    void receive_ping() {
        t_ping *ping = get_ping();
        char buf[1024];
        struct sockaddr_in  from;
        socklen_t           from_len = sizeof(from);
        struct ip           *ip_header;
        t_icmp_header       *icmp;
        struct timeval      time_start, time_stop;
        double              rtt;
        int                 bytes;
        
        bytes = recvfrom(ping->sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&from, &from_len);
        if (bytes < 0)
            ft_err("recvfrom failed\n", 1);

        gettimeofday(&time_stop, NULL);

        if (!valid_icmp(buf, bytes))
            return;

        ip_header = (struct ip *)buf;
        icmp = (t_icmp_header *)(buf + (ip_header->ip_hl * 4));
        
        memcpy(&time_start, icmp->payload, sizeof(time_start));

        rtt = (time_stop.tv_sec - time_start.tv_sec) * 1000
            + (time_stop.tv_usec - time_start.tv_usec) / 1000;

        ping->received++;

        if (ping->min_rtt == 0 || rtt < ping->min_rtt)
            ping->min_rtt = rtt;
        
        if (rtt > ping->max_rtt)
            ping->max_rtt = rtt;
        
        ping->mix_rtt += rtt;

        printf("%zu bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", 
                sizeof(t_icmp_header), inet_ntoa(from.sin_addr), \
                icmp->sequence, ip_header->ip_ttl, rtt);

    }