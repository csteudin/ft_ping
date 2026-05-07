#include "../inc/ping.h"

/*
    - PRINT AND EXIT -
    + prints the formatted help section 
*/
    void	print_and_exit()    {
        printf("XXX, HOW TO USE ZZZ zzz");
        
        exit(1);
    }

    void print_start()  {
        t_ping *ping = get_ping();

        printf("XXX: started to ping %s\n", ping->domain);
    }

    void print_stats()  {
        
    }