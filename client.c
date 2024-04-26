/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:25:15 by mamir             #+#    #+#             */
/*   Updated: 2024/04/26 15:41:39 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_error(void)
{
	write(2, "BAD INPUT!\n", 10);
	exit(1);
}

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

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	if (ac != 3)
		ft_error();
	if (!ft_check(av[1]))
		ft_error();
	pid = ft_atoi(av[1]);
	i = 0;
	if (pid <= 1 && pid >= -1)
	{
		write(2, "Wrong Pid\n", 21);
		exit(1);
	}
	while (av[2][i] != '\0')
	{
		send_message(pid, av[2][i++]);
		usleep(500);
	}
	send_message(pid, '\0');
	return (0);
}
