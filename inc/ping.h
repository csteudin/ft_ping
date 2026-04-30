#ifndef PING_H
#define PING_H

//--* / = \ *-----

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

typedef enum e_flag
{
	COUNT,
	TTL,
	INTERVAL
}	t_flag;

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
	bool	set_host;
	bool	verbose;

	int		count;
	double	interval;
	int		ttl;

	char *ip_str;
	char domain[256];

	char dest_ip[INET_ADDRSTRLEN];
	struct sockaddr_in dest_addr;

} t_ping;

// main
void initialize();
int main(int ac, char **av);

// print
void	print_and_exit();

// parcing
void	handle_host(char *token);
void	check_flag(char **av, int *i, t_flag flag);
void	handle_flag(char *token, char **av, int *i);
void	check_input(int ac, char **av);
// socket
void resolve_host();

// utils
int		is_float(const char *str);
int		is_number(const char *str);
int		ft_err(char *str, int ex_code);
t_ping	*get_ping(void);

#endif