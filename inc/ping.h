#ifndef PING_H
#define PING_H
//--* / = \ *-----

#include <cstdint>
#include <stdio.h>

typedef struct s_ping
{
	bool	vebose;
	bool	help;

	int64_t	ip;
	char 	*domain;
} t_ping;

int check_input(int ac, char **av);

#endif