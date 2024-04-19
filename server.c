#include "minitalk.h"

// void signal_handler(int signum)
// {
    
// }

int main()
{
    pid_t pid;
    pid = getpid();
    printf("PID:%d\n",pid);


    // while (1)
    // {
    // signal(SIGUSR1, signal_handler);
    // signal(SIGUSR2, signal_handler);
        
    // }

    return 0;
}