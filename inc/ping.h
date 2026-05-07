#ifndef PING_H
#define PING_H

//--* / = \ *-----

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <signal.h>
#include <ctype.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>
#include <sys/time.h>
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
	int		sockfd;

	char *ip_str;
	char domain[256];

	char dest_ip[INET_ADDRSTRLEN];
	struct sockaddr_in dest_addr;

	int sequence;

	int sent;
	int received;

	double min_rtt;
	double max_rtt;
	double mix_rtt;
} t_ping;

// main
void	initialize();
void	ping_loop();
int		main(int ac, char **av);

// connection
uint16_t checksum(void *buf, int len);
void 	send_ping();
void 	receive_ping();

// print
void	print_and_exit();
void	print_start();

// signals
//void	setup_signals();
void	handle_sigint(int sig);

// parcing
void	handle_host(char *token);
void	check_flag(char **av, int *i, t_flag flag);
void	handle_flag(char *token, char **av, int *i);
void	check_input(int ac, char **av);
int		valid_icmp(char *buf, int len);

// socket
void	setup_socket();
void	resolve_host();

// utils
int		is_float(const char *str);
int		is_number(const char *str);
int		ft_err(char *str, int ex_code);
t_ping	*get_ping(void);

#endif