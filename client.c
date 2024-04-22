#include "minitalk.h"

int ft_atoi(const char *str)
{
    int i;
    long r;
    long s;

    i = 0;
    r = 0;
    s = 1;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-')
    {
        s = -1;
        i++;
    }
    else if (str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        if (r > 2147483647)
        {
            write(2, "BAD PID!\n", 10);
            exit(1);
        }
        r = r * 10 + (str[i] - '0');
        i++;
    }
    return (r * s);
}

void send_message(int pid ,char c)
{
    int i;
    unsigned char tmp;

    if (pid <= 0)
    {
        write(2, "BAD PID!\n", 10);
        exit(1);
    }

    i = 7;
    while (i >= 0)
    {
        tmp = c >> i;
        if (tmp % 2 == 0)
            kill(pid, SIGUSR2);
        else     
            kill(pid, SIGUSR1);
        i--;
        usleep(500);
    }
}

int main(int ac, char **av)
{
    int pid;
    int i;

    if (ac != 3)
    {
        write(2, "Wrong Input!\n", 14);
        exit(1);
    }
    pid = ft_atoi(av[1]);
    i = 0;
    while (av[2][i] != '\0')
    {
        send_message(pid, av[2][i++]);
        usleep(500);
    }
    send_message(pid,'\0');
    return 0;
}