#include "../inc/ping.h"

/*
    - IS FLOAT -
    + checks if the given string is a valid float
    + checks for + chars, and double . ex.  <1.22.78>
*/
    int is_float(const char *str)   {
        bool dot = false;
        int i = 0;

        if (!str || !str[0])
            return (1);

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
        return (0);
    }
    
/*
    - IS NUMBER -
    + checks if the given string is a valid number
    + checks for +, and exceptions ++
*/
    int is_number(const char *str)    {
        int len;
        int i = 0;
        
        if (!str || !str[0])
            return (1);
        len = strlen(str);
        if (str[i] == '+')
            i++;
        if (i == len)
            return (1);

        while(i < len)
        {
            if (!isdigit(str[i]))
                return (1);
            i++;
        }
        return (0);
    }

/*
    - FT_ERR -
    + prints a1 and exits with a2
*/
    int ft_err(char *str, int ex_code)
    {
        fprintf(stderr, "%s", str);
        //free_function
        exit(ex_code);
    }


/*
    - GET PING -
    + static singleton function <t_ping *>
    + always returns the same memory adress, code magic
    + is eficcient because we dont allocate it
    + fast acces to main struct
*/
    t_ping *get_ping(void)
    {
        static t_ping ping;

        return (&ping);
    }