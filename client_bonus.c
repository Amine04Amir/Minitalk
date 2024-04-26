/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:25:15 by mamir             #+#    #+#             */
/*   Updated: 2024/04/24 15:46:44 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int		g_pid;

int	ft_atoi(const char *str)
{
	int		i;
	long	r;
	int		s;

	i = 0;
	r = 0;
	s = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		if (r > 2147483647)
			ft_error();
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (r * s);
}

int	ft_check(char *str)
{
	if (ft_atoi(str) == 0)
	{
		if (*str == '+' || *str == '-')
			str++;
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		while (*str == '0')
			str++;
		if (*str != '\0')
			return (0);
	}
	return (1);
}

void	send_message(int pid, unsigned char c)
{
	int				i;
	unsigned char	tmp;

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

void	receive_message(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (sig == SIGUSR1 || info->si_pid == g_pid)
	{
		write(1, "Message recieved !!\n", 20);
	}
	return ;
}

int	main(int ac, char **av)
{
	int					pid;
	int					i;
	struct sigaction	sa;

	if (ac != 3)
		ft_error();
	sa.sa_sigaction = &receive_message;
	sigaction(SIGUSR1, &sa, NULL);
	if (!ft_check(av[1]))
		ft_error();
	pid = ft_atoi(av[1]);
	g_pid = pid;
	i = 0;
	if (pid <= 1 && pid >= -1)
		ft_error();
	while (av[2][i] != '\0')
	{
		send_message(pid, av[2][i++]);
		usleep(500);
	}
	send_message(pid, '\0');
	return (0);
}
