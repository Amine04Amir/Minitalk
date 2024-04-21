#include "minitalk.h"

t_data data ={.bit = 0, .index = 0};

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void ft_putnbr(int n)
{
    if (n == -2147483648)
        write(1, "-2147483648", 11);
    else if (n < 0)
    {
        ft_putchar('-');
        n = -n;
        ft_putnbr(n);
    }
    else if (n >= 10)
    {
        ft_putnbr(n / 10);
        ft_putnbr(n % 10);
    }
    else if (n >= 0 && n <= 9)
        ft_putchar(n +48);
}

void signal_handler(int signum)
{
    if (signum == SIGUSR1)
        data.bit |= 1;
    data.index++;
    if (data.index == 8)
    {
        if (data.bit == '\0')
            write(1, "\n", 2);  
        write(1, &data.bit, 1);
        data.index = 0;
        data.bit = 0;
    }
    data.bit <<= 1;
}

int main()
{
    pid_t pid;

    pid = getpid();
    write(1, "PID:", 5);
    ft_putnbr(pid);
    write(1, "\n", 1);
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2,signal_handler);
    while (1)
    {
        pause();
    }
    return 0;
}