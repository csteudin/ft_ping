#include "../inc/ping.h"

int is_float(const char *str)   {
    bool dot = false;
    int i = 0;

    if (str[i] == '+')
        i++;
    
    if (!isdigit(str[i]) && str[i] != '.')
        return (1);
    
    while(str[i])   {
        if (str[i] == '.')
        {
            if(dot)
                return (1);
            dot = 1;
        }
        else if (!isdigit(str[i]))
            return (1);
        i++;
    }
    return 0;
}

int is_number(const char *str)    {
    int len = strlen(str);
    int i = 0;
    
    if (str[i] == '+')
        i++;
    if (str[i] == '+')
        ft_err("XXX: invalid argument\n", 1);

    while(i < len)
    {
        if (!isdigit(str[i]))
            return (1);
        i++;
    }
    return (0);
}

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