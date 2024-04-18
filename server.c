#include "minitalk.h"

int main()
{
    pid_t pid;
    pid = getpid();
    printf("PID:%d\n", pid);
    signal();
    return 0;
}