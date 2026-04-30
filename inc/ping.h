#ifndef PING_H
#define PING_H

//--* / = \ *-----

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <sys/socket.h>

typedef struct icmp_header
{
	uint8_t type;
	uint8_t code;
	uint16_t checksum;
	uint16_t id;
	uint16_t sequence;
	char payload[56];
} t_icmp_header;

typedef struct s_ping
{
	bool	verbose;

	char *ip_str;
	char *domain;
	int64_t	ip;
	struct sockaddr_in *dest_addr;

} t_ping;

// print
void print_and_exit();

// parcing
void handle_host(char *token);
void handle_flag(char *token);
void check_input(int ac, char **av);

// utils
int ft_err(char *str, int ex_code);
t_ping *get_ping(void);

#endif