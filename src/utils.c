#include "../inc/ping.h"

int ft_err(char *str, int ex_code)
{
    fprintf(stderr, "%s", str);
    //free_function
    exit(ex_code);
}

t_ping *get_ping(void)
{
    static t_ping ping;

    return (&ping);
}